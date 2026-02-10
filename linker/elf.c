#include <unistd.h>
#include <string.h>
#include <fcntl.h>
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

struct elf_object *elf_load(const char *path) {
	struct elf_object *object = dl_alloc(sizeof(struct elf_object));
	memset(object, 0, sizeof(struct elf_object));

	int file = open(path, O_RDONLY);
	if (file < 0) {
		dl_error("cannot open file");
		goto free;
	}
	object->fd = file;

	if (read(file, &object->header,sizeof(Elf_Ehdr)) < sizeof(Elf_Ehdr)) {
		dl_error("read failed");
		goto close;
	}
	if (!check_ehdr(&object->header)) {
		dl_error("invalid elf header");
		goto close;
	}

	if (object->header.e_type == ET_DYN) {
		// TODO : alloc space for the lib
	}

	object->phdr_count = object->header.e_phnum;
	object->phdr = dl_alloc(sizeof(Elf_Phdr) * object->phdr_count);
	uintptr_t off = object->header.e_phoff;
	for (int i=0; i<object->header.e_phnum; i++,off += object->header.e_phentsize) {
		Elf_Phdr *pheader = &object->phdr[i];
		lseek(file, off, SEEK_SET);
		if (read(file, pheader, sizeof(*pheader)) < sizeof(*pheader)) {
			dl_error("read failed");
			goto close;
		}
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
		if (pheader->p_offset % PAGE_SIZE != pheader->p_vaddr % PAGE_SIZE) {
			dl_error("invalid mapping");
			goto close;
		}

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

		char *vaddr = (char*)object->addr + PAGE_ALIGN_DOWN(pheader->p_vaddr);
		size_t vaddr_off = pheader->p_vaddr % PAGE_SIZE;
		if (pheader->p_filesz > 0) {
			if (mmap(vaddr, vaddr_off + pheader->p_filesz, prot, MAP_PRIVATE, file, PAGE_ALIGN_DOWN(pheader->p_offset)) == MAP_FAILED) {
				dl_error("mmap failed");
				goto close;
			}
		}
		if (pheader->p_memsz > pheader->p_filesz) {
			// we have to fill with anonymous mappings
			if (mmap(vaddr + pheader->p_filesz, vaddr_off + pheader->p_memsz - pheader->p_filesz, prot, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0) == MAP_FAILED) {
				dl_error("mmap failed");
				goto close;
			}
		}
	}

free:
	elf_unload(object);
close:
	close(file);
	return NULL;
}

void elf_unload(struct elf_object *object) {
	// TODO : unload and free depencies
	dl_free(object->name);
	dl_free(object->phdr);
	dl_free(object->dynamics);
	dl_free(object);
}

void *elf_lookup(struct elf_object *object, const char *name) {
	return NULL;
}
