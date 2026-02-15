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
			if (mmap((void*)vaddr, filesz, PROT_WRITE, MAP_PRIVATE | MAP_FIXED, file, offset) == MAP_FAILED) {
				return dl_error("mmap failed");
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
			if (mmap((void*)vaddr, memsz - filesz, prot, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, 0, 0) == MAP_FAILED) {
				// remove the aready mapped part
				munmap((void*)(vaddr-filesz), filesz);
				return dl_error("mmap failed");
			}
		}
	} else {
		size_t memsz = PAGE_ALIGN_UP(pheader->p_memsz + vaddr_off);

		if (mmap((void*)vaddr, memsz, PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, 0, 0) == MAP_FAILED) {
			return dl_error("mmap failed");
		}

		// file size must be <= to virtual size
		if (pheader->p_filesz > pheader->p_memsz) {
			pheader->p_filesz = pheader->p_memsz;
		}

		lseek(file, pheader->p_offset, SEEK_SET);
		if (read(file, (void *)(vaddr + vaddr_off), pheader->p_filesz) < pheader->p_filesz) {
			munmap((void*)vaddr, memsz);
			return dl_error("read failed");
		}
		// set the protection
		mprotect((void*)vaddr, memsz, prot);
	}
	return 0;
}

static int load_dynamics(struct elf_object *object, int file, Elf_Phdr *pheader, Elf_Dyn dynamics[DT_BIND_NOW+1]) {
	// dynamics section must be aligned
#if defined(__x86_64__) || defined(__aarch64__)
	size_t align = 8;
#elif defined(__i386__)
	size_t align = 4;
#else
	size_t align = 1;
#endif
	if (pheader->p_offset % align) {
		return dl_error("unaligned PT_DYNAMIC section");
	}

	off_t offset = PAGE_ALIGN_DOWN(pheader->p_offset);
	size_t remainer = pheader->p_offset;
	size_t size = PAGE_ALIGN_UP(pheader->p_filesz);
	void *addr = mmap(NULL, size, PROT_READ, MAP_PRIVATE, file, offset);
	if (addr == MAP_FAILED) {;
		return dl_error("mmap failed");
	}

	Elf_Dyn *dyns = (Elf_Dyn*)((uintptr_t)addr + remainer);
	size_t dyns_count = pheader->p_filesz / sizeof(Elf_Dyn);
	for (size_t i=0; i<dyns_count; i++) {
		if (dyns[i].d_tag == DT_NULL) break;
		if (dyns[i].d_tag <= DT_BIND_NOW) {
			dynamics[dyns[i].d_tag] = dyns[i];
		}
	}
	munmap(addr, size);
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

static int handle_dynamics(struct elf_object *object, int file, Elf_Dyn dynamics[DT_BIND_NOW+1]) {
	if (!dynamics[DT_STRTAB].d_un.d_ptr || !dynamics[DT_STRTAB].d_un.d_val) {
		return dl_error("no string table");
	}
	// TODO : load string table and more
	return 0;
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

	Elf_Dyn dynamics[DT_BIND_NOW+1] = {0};

	for (int i=0; i<object->phdrs_count; i++) {
		Elf_Phdr *pheader = &object->phdrs[i];
		switch (pheader->p_type) {
		case PT_DYNAMIC:
			if (load_dynamics(object, file, pheader, dynamics) < 0) goto close;
			break;
		case PT_LOAD:
			if (map_segment(object, file, pheader) < 0) goto close;
			break;
		}
	}

	if (handle_dynamics(object, file, dynamics) < 0) {
		goto close;
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
	dl_free(object);
}

void *elf_lookup(struct elf_object *object, const char *name) {
	return NULL;
}
