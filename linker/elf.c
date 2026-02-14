#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/mman.h>
#include <elf.h>
#include "linker.h"


static int check_ehdr(Elf64_Ehdr *header){
	if (memcmp(header->e_ident, ELFMAG, 4)) {
		return 0;
	}
	if (header->e_ident[EI_CLASS] != ELFCLASS) {
		return 0;
	}
	if (header->e_version != EV_CURRENT) {
		return 0;
	}
	return 1;
}

static int map_segment(struct elf_object *object, int file, Elf_Phdr *pheader) {
	int prot = 0;
	if (pheader->p_flags & PF_R) {
		prot |= PROT_READ;
	}
	if (pheader->p_flags & PF_W) {
		prot |= PROT_WRITE;
	}
	if (pheader->p_flags & PF_X) {
		prot |= PROT_EXEC;
	}

	// page align everything
	uintptr_t vaddr = PAGE_ALIGN_DOWN(pheader->p_vaddr) + object->addr;
	size_t vaddr_off = pheader->p_vaddr % PAGE_SIZE;

	if (pheader->p_offset % PAGE_SIZE == pheader->p_vaddr % PAGE_SIZE) {
		// we can use mmap

		off_t offset = PAGE_ALIGN_DOWN(pheader->p_offset);
		size_t filesz = PAGE_ALIGN_UP(pheader->p_filesz + vaddr_off);
		size_t memsz  = PAGE_ALIGN_UP(pheader->p_memsz + vaddr_off);
		size_t filesz_remainer = 0;

		if (memsz > filesz && (pheader->p_filesz + vaddr_off) % PAGE_SIZE) {
			filesz_remainer = (pheader->p_filesz + vaddr_off) % PAGE_SIZE;
		}

		if (filesz > 0) {
			if (mmap((void*)vaddr, filesz, PROT_WRITE, MAP_PRIVATE | MAP_FIXED, file, offset) < 0) {
				return -1;
			}
			// zero the last page
			if (filesz_remainer) {
				uintptr_t start_bss = vaddr + filesz - PAGE_SIZE + filesz_remainer;
				memset((void*)start_bss, 0, PAGE_SIZE - filesz_remainer);
			}
			mprotect((void*)vaddr, filesz, prot);
		}
		if (memsz > filesz) {
			// we need to fill with anonymous mapping
			vaddr += filesz;
			if (mmap((void*)vaddr, memsz - filesz, prot, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, 0, 0) < 0) {
				// remove the already mapped part
				munmap((void*)(vaddr-filesz), filesz);
				return -1;
			}
		}
	} else {
		size_t memsz = PAGE_ALIGN_UP(pheader->p_memsz + vaddr_off);

		if (mmap((void*)vaddr, memsz, PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, 0, 0) < 0) {
			return -1;
		}

		// file size must be <= to virtual size
		if (pheader->p_filesz > pheader->p_memsz) {
			pheader->p_filesz = pheader->p_memsz;
		}

		lseek(file, pheader->p_offset, SEEK_SET);
		if (read(file, (void *)(vaddr + vaddr_off), pheader->p_filesz) < pheader->p_filesz) {
				munmap((void*)vaddr, memsz);
				return -1;
		}
		// set the protection
		mprotect((void*)vaddr, memsz, prot);
	}
	return 0;
}

static size_t get_total_size(struct elf_object *object) {
	uintptr_t start = UINTPTR_MAX;
	uintptr_t end   = 0;
	for (int i=0; i<object->phdrs_count; i++) {
		Elf_Phdr *pheader = &object->phdrs[i];
		if (pheader->p_type != PT_LOAD) continue;
		if (PAGE_ALIGN_DOWN(pheader->p_vaddr) < start) {
			start = PAGE_ALIGN_DOWN(pheader->p_vaddr);
		}
		if (PAGE_ALIGN_UP(pheader->p_vaddr + pheader->p_memsz) > end) {
			end = PAGE_ALIGN_UP(pheader->p_vaddr + pheader->p_memsz);
		}
	}
	if (start > end) return 0;
	return end - start;
}

struct elf_object *elf_load(const char *path) {
	struct elf_object *object = dl_alloc(sizeof(struct elf_object));
	memset(object, 0, sizeof(struct elf_object));

	int file = open_lib(path);
	if (file < 0) {
		dl_error("cannot open file");
		goto free;
	}

	if (read(file, &object->header,sizeof(Elf_Ehdr)) < sizeof(Elf_Ehdr)) {
		dl_error("read failed");
		goto close;
	}
	if (!check_ehdr(&object->header)) {
		dl_error("invalid elf header");
		goto close;
	}

	// load phdrs
	object->phdrs_count = object->header.e_phnum;
	object->phdrs = dl_alloc(sizeof(Elf_Phdr) * object->phdrs_count);
	uintptr_t off = object->header.e_phoff;
	for (int i=0; i<object->header.e_phnum; i++,off += object->header.e_phentsize) {
		Elf_Phdr *pheader = &object->phdrs[i];
		lseek(file, off, SEEK_SET);
		if (read(file, pheader, sizeof(*pheader)) < sizeof(*pheader)) {
			dl_error("read failed");
			goto close;
		}
	}

	if (object->header.e_type == ET_DYN) {
		// allocate space for the lib
		void *addr = mmap(NULL, get_total_size(object), 0, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
		if (addr == MAP_FAILED) {
			dl_error("mmap failed");
			goto close;
		}
		object->addr = (uintptr_t)addr;
	}

	for (int i=0; i<object->phdrs_count; i++) {
		Elf_Phdr *pheader = &object->phdrs[i];
		if (pheader->p_type == PT_DYNAMIC) {
			// two PT_DYNAMIC ???? ignore i guess
			if (object->dynamics) continue;
			object->dynamics = dl_alloc(pheader->p_filesz);
			lseek(file, pheader->p_offset, SEEK_SET);
			read(file, object->dynamics, pheader->p_filesz);

			for (size_t j=0; j<pheader->p_filesz; j+=sizeof(Elf_Dyn)) {
				if (object->dynamics[i].d_tag == DT_NULL) break;
				object->dynamics_count++;
				switch (object->dynamics[i].d_tag) {
				}
			}
		}
		if (pheader->p_type != PT_LOAD) continue;
		if (map_segment(object, file, pheader) < 0) {
			dl_error("mmap failed");
			goto close;
		}
	}

	close(file);
	return object;

close:
	close(file);
free:
	elf_unload(object);
	return NULL;
}

void elf_unload(struct elf_object *object) {
	// TODO : unload and free depencies
	if (object->header.e_type == ET_DYN) {
		// we can free the whole allocated block
		munmap((void*)object->addr, get_total_size(object));
	}
	dl_free(object->name);
	dl_free(object->phdrs);
	dl_free(object->dynamics);
	dl_free(object);
}

void *elf_lookup(struct elf_object *object, const char *name) {
	return NULL;
}
