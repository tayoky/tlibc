#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/mman.h>
#include <elf.h>
#include "linker.h"

static int check_ehdr(Elf_Ehdr *header, int is_lib){
	if (memcmp(header->e_ident, ELFMAG, 4)) {
		return 0;
	}
	if (header->e_ident[EI_CLASS] != ELFCLASS) {
		return 0;
	}
	if (header->e_version != EV_CURRENT) {
		return 0;
	}
	if (is_lib) {
		if (header->e_type != ET_DYN) {
			return 0;
		}
	} else {
		if (header->e_type != ET_EXEC) {
			return 0;
		}
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
		if (read(file, (void *)(vaddr + vaddr_off), pheader->p_filesz) < (ssize_t)pheader->p_filesz) {
			munmap((void*)vaddr, memsz);
			return dl_error("read failed");
		}
		// set the protection
		mprotect((void*)vaddr, memsz, prot);
	}
	return 0;
}

static int load_dynamics(int file, Elf_Phdr *pheader, Elf_Dyn dynamics[DT_BIND_NOW+1]) {
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
	size_t remainer = pheader->p_offset % PAGE_SIZE;
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
	for (size_t i=0; i<object->phdrs_count; i++) {
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

static void *load_table(int file, off_t offset, size_t size) {
	size_t remainer = offset % PAGE_SIZE;
	offset = PAGE_ALIGN_DOWN(offset);
	size = PAGE_ALIGN_UP(size + remainer);
	void *addr = mmap(NULL, size, PROT_READ, MAP_PRIVATE, file, offset);
	if (addr == MAP_FAILED) return NULL;
	return (void*)((uintptr_t)addr +  remainer);
}

static void unload_table(void *ptr, size_t size) {
	if (!ptr) return;
	uintptr_t addr = (uintptr_t)ptr;
	size_t remainer = addr % PAGE_SIZE;
	ptr = (void*)PAGE_ALIGN_DOWN(addr);
	size = PAGE_ALIGN_UP(size + remainer);
	munmap(ptr, size);
}

static const char *get_str(struct elf_object *object, size_t offset) {
	const char *str = object->strtab + offset;
	const char *cur = str;
	const char *strtab_end = object->strtab + object->strtab_size;

	// check if the string is in bounds
	while (cur < strtab_end) {
		if (!*cur) return str;
		cur++;
	}
	dl_error("invalid string offset");
	return NULL;
}

static int handle_dynamics(struct elf_object *object, int file, Elf_Dyn dynamics[DT_BIND_NOW+1]) {
	if (!dynamics[DT_STRTAB].d_un.d_ptr || !dynamics[DT_STRSZ].d_un.d_val) {
		return dl_error("no string table");
	}
	object->strtab_size = dynamics[DT_STRSZ].d_un.d_val;
	object->strtab = load_table(file, dynamics[DT_STRTAB].d_un.d_ptr, object->strtab_size);
	if (!object->strtab) return -1;

	if (!dynamics[DT_SYMTAB].d_un.d_ptr || !dynamics[DT_HASH].d_un.d_val) {
		return dl_error("no symtab table");
	}

	// start by firguring out the size of the hash and symbol table
	uint32_t hash_start[2];
	lseek(file, dynamics[DT_HASH].d_un.d_ptr, SEEK_SET);
	if (read(file, hash_start, sizeof(hash_start)) < (ssize_t)sizeof(hash_start)) {
		return dl_error("read failed");
	}

	// nchain (second entry) contain symtab entries count
	object->symbols_count = hash_start[1];
	object->symtab = load_table(file, dynamics[DT_SYMTAB].d_un.d_ptr, object->symbols_count * sizeof(Elf_Sym));
	if (!object->symtab) return -1;

	// 2 + nbucket + nchain give total entries count
	// we can use that to load hash table
	object->hash_size = (2 + hash_start[0] + hash_start[1]) * sizeof(uint32_t);
	object->hash = load_table(file, dynamics[DT_HASH].d_un.d_ptr, object->hash_size);

	// optional DT_RPATH for executables
	if (object->header.e_type == ET_EXEC && dynamics[DT_RPATH].d_un.d_val) {
		rpath = get_str(object, dynamics[DT_RPATH].d_un.d_val);
		if (!rpath) return -1;
	}
	return 0;
}

struct elf_object *elf_load(const char *path, int is_lib) {
	struct elf_object *object = dl_alloc(sizeof(struct elf_object));
	memset(object, 0, sizeof(struct elf_object));

	int file = open_lib(path);
	if (file < 0) {
		dl_error("cannot open file");
		goto free;
	}

	if (read(file, &object->header,sizeof(Elf_Ehdr)) < (ssize_t)sizeof(Elf_Ehdr)) {
		dl_error("read failed");
		goto close;
	}
	if (!check_ehdr(&object->header, is_lib)) {
		dl_error("invalid elf header");
		goto close;
	}

	// load phdrs
	object->phdrs_count = object->header.e_phnum;
	object->phdrs = dl_alloc(sizeof(Elf_Phdr) * object->phdrs_count);
	uintptr_t off = object->header.e_phoff;
	for (size_t i=0; i<object->header.e_phnum; i++,off += object->header.e_phentsize) {
		Elf_Phdr *pheader = &object->phdrs[i];
		lseek(file, off, SEEK_SET);
		if (read(file, pheader, sizeof(*pheader)) < (ssize_t)sizeof(*pheader)) {
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

	for (size_t i=0; i<object->phdrs_count; i++) {
		Elf_Phdr *pheader = &object->phdrs[i];
		switch (pheader->p_type) {
		case PT_DYNAMIC:
			if (load_dynamics(file, pheader, dynamics) < 0) goto close;
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
	unload_table(object->strtab, object->strtab_size);
	unload_table(object->symtab, object->symbols_count * sizeof(Elf_Sym));
	unload_table(object->hash, object->hash_size);
	dl_free(object->name);
	dl_free(object->phdrs);
	dl_free(object);
}

// taken from the ELF spec
static unsigned long elf_hash(const unsigned char *name) {
	unsigned long h = 0, g;

	while (*name) {
		h = (h << 4) + *name++;
		if ((g = h) & 0xf0000000)
			h ^= g >> 24;
		h &= ~g;
	}
	return h;
}

void *elf_lookup(struct elf_object *object, const char *name) {
	uint32_t hash = elf_hash((const unsigned char*)name);
	uint32_t nbucket = object->hash[0];
	uint32_t nchain  = object->hash[1];
	uint32_t *bucket = object->hash + 2;
	uint32_t *chain = object->hash + 2;
	size_t index = bucket[hash % nbucket];
	while (index != SHN_UNDEF) {
		if (index >= nchain) {
			// uh
			dl_error("invalid index in hash table");
			return NULL;
		}

		Elf_Sym *sym = &object->symtab[index];
		const char *sym_name = get_str(object, sym->st_name);
		if (!sym_name) {
			dl_error("invalid symbol");
			return NULL;
		}
		if (!strcmp(name, sym_name)) {
			// we found it
			return (void*)(sym->st_value + object->addr);
		}

		// go to next entry
		index = chain[index];
	}
	dl_error("symbol not found");
	return NULL;
}
