#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <sys/mman.h>
#include <stdio.h>
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
	if (!is_lib) {
		// executables must have an entry point
		if (header->e_entry == 0) {
			return 0;
		}
	}
	return 1;
}

static int map_segment(struct elf_object *object, int file, Elf_Phdr *pheader) {
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
		}
		if (memsz > filesz) {
			// we need to fill with anonymous mapping
			vaddr += filesz;
			if (mmap((void*)vaddr, memsz - filesz, PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, 0, 0) == MAP_FAILED) {
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
	}
	return 0;
}

static int set_protections(struct elf_object *object) {
	for (size_t i=0; i<object->phdrs_count; i++) {
		int prot = 0;
		if (object->phdrs[i].p_flags & PF_R) {
			prot |= PROT_READ;
		}
		if (object->phdrs[i].p_flags & PF_W) {
			prot |= PROT_WRITE;
		}
		if (object->phdrs[i].p_flags & PF_X) {
			prot |= PROT_EXEC;
		}
		uintptr_t start = PAGE_ALIGN_DOWN(object->phdrs[i].p_vaddr);
		uintptr_t end   = PAGE_ALIGN_UP(object->phdrs[i].p_vaddr);
		mprotect((void*)start, end - start, prot);
	}
	return 0;
}

const char *get_str(struct elf_object *object, size_t offset) {
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

static Elf_Dyn *find_dynamic(struct elf_object *object, long tag) {
	for (size_t i=0; object->dynamics[i].d_tag != DT_NULL; i++) {
		if (object->dynamics[i].d_tag == tag) {
			return &object->dynamics[i];
		}
	}
	return NULL;
}

// TODO : check pointers are in bound
static int handle_dynamics(struct elf_object *object) {
	Elf_Dyn *dyn_strtab = find_dynamic(object, DT_STRTAB);
	Elf_Dyn *dyn_strsz  = find_dynamic(object, DT_STRSZ);
	Elf_Dyn *dyn_symtab = find_dynamic(object, DT_SYMTAB);
	Elf_Dyn *dyn_hash   = find_dynamic(object, DT_HASH);
	Elf_Dyn *dyn_rpath  = find_dynamic(object, DT_RPATH);

	if (!dyn_strtab || !dyn_strsz) {
		return dl_error("no string table");
	}
	object->strtab_size = dyn_strsz->d_un.d_val;
	object->strtab = (void*)(dyn_strtab->d_un.d_ptr + object->addr);
	if (!object->strtab) return -1;

	if (!dyn_symtab || !dyn_hash) {
		return dl_error("no symtab table");
	}

	// start by firguring out the size of the hash and symbol table
	uint32_t *hash_start = (void*)(dyn_hash->d_un.d_ptr + object->addr);

	// nchain (second entry) contain symtab entries count
	object->symbols_count = hash_start[1];
	object->symtab = (void*)(dyn_symtab->d_un.d_ptr + object->addr);

	// 2 + nbucket + nchain give total entries count
	// we can use that to load hash table
	object->hash_size = (2 + hash_start[0] + hash_start[1]) * sizeof(uint32_t);
	object->hash = (void*)(dyn_hash->d_un.d_ptr + object->addr);

	// relocate symbols
	for (size_t i=0; i<object->symbols_count; i++){
		Elf_Sym *sym = &object->symtab[i];
		if (sym->st_shndx == SHN_UNDEF) continue;
		if (sym->st_shndx == SHN_ABS) continue;
		sym->st_value += object->addr;
	}

	// optional DT_RPATH for executables
	if (object->header.e_type == ET_EXEC && dyn_rpath) {
		rpath = get_str(object, dyn_rpath->d_un.d_val);
		if (!rpath) return -1;
	}

	// determinate depencies count
	object->depencies_count = 0;
	for (size_t i=0; object->dynamics[i].d_tag != DT_NULL; i++) {
		if (object->dynamics[i].d_tag != DT_NEEDED) continue;
		object->depencies_count++;
	}
	object->depencies = dl_alloc(object->depencies_count * sizeof(struct elf_object*));
	memset(object->depencies, 0, object->depencies_count * sizeof(struct elf_object*));

	// and load them
	size_t index = 0;
	for (size_t i=0; object->dynamics[i].d_tag != DT_NULL; i++) {
		if (object->dynamics[i].d_tag != DT_NEEDED) continue;
		const char *name = get_str(object, object->dynamics[i].d_un.d_val);
		if (!name) return -1;

		if (dl_debug) fprintf(stderr, "ld-tlibc.so : find depencie '%s'\n", name);
		void *lib = dlopen(name, RTLD_NOW | RTLD_LOCAL);
		if (!lib) {
			dl_error("cannot access a needed shared library");
			return -1;
		}
		object->depencies[index++] = lib;
	}
	return 0;
}

static int apply_relocs(struct elf_object *object) {
	Elf_Dyn *dyn_rela    = find_dynamic(object, DT_RELA);
	Elf_Dyn *dyn_relasz  = find_dynamic(object, DT_RELASZ);
	Elf_Dyn *dyn_relaent = find_dynamic(object, DT_RELAENT);
	Elf_Dyn *dyn_rel    = find_dynamic(object, DT_REL);
	Elf_Dyn *dyn_relsz  = find_dynamic(object, DT_RELSZ);
	Elf_Dyn *dyn_relent = find_dynamic(object, DT_RELENT);
	Elf_Dyn *dyn_jmprel = find_dynamic(object, DT_JMPREL);
	Elf_Dyn *dyn_plt_rel_sz  = find_dynamic(object, DT_PLTRELSZ);
	(void)dyn_rela;
	(void)dyn_relasz;
	(void)dyn_relaent;
	(void)dyn_rel;
	(void)dyn_relsz;
	(void)dyn_relent;

	int type = 0;
#if defined(__x86_64__) || defined(__i386__)
	type = DT_RELA;
#endif
	if (!type) {
		// TODO : use PLTREL or something
		type = DT_RELA;
	}
	
	if (!dyn_jmprel || !dyn_plt_rel_sz) {
		return dl_error("no relocation table");
	}

	size_t rel_ent;
	void *plt_table = (void*)(dyn_jmprel->d_un.d_ptr + object->addr);
	size_t plt_rel_size = dyn_plt_rel_sz->d_un.d_val;
	void *table;
	size_t rel_size;
	switch (type) {
	case DT_RELA:
		if (!dyn_rela || !dyn_relasz || !dyn_relaent) {
			return dl_error("no relocation table");
		}
		rel_size = dyn_relasz->d_un.d_val;
		rel_ent = dyn_relaent->d_un.d_val;
		table = (void*)(dyn_rela->d_un.d_ptr + object->addr);
		break;
	case DT_REL:
		if (!dyn_rel || !dyn_relsz || !dyn_relent) {
			return dl_error("no relocation table");
		}
		rel_size = dyn_relsz->d_un.d_val;
		rel_ent = dyn_relent->d_un.d_val;
		table = (void*)(dyn_rel->d_un.d_ptr + object->addr);
		break;
	}
	if (!plt_table) {
		return -1;
	}

	// dynamic relocs
	for (size_t i=0; i<rel_size; i+=rel_ent) {
		uintptr_t addr = (uintptr_t)table + i;
		if (reloc(object, (Elf_Rela*)addr) < 0) return -1;
	}

	// plt relocs
	for (size_t i=0; i<plt_rel_size; i+=rel_ent) {
		uintptr_t addr = (uintptr_t)plt_table + i;
		if (reloc(object, (Elf_Rela*)addr) < 0) return -1;
	}

	return 0;
}

static void call_constructors(struct elf_object *object) {
	Elf_Dyn *dyn_init            = find_dynamic(object, DT_INIT);
	Elf_Dyn *dyn_init_array      = find_dynamic(object, DT_INIT_ARRAY);
	Elf_Dyn *dyn_init_arraysz    = find_dynamic(object, DT_INIT_ARRAYSZ);
	if (dyn_init) {
		func_t init = (void*)(dyn_init->d_un.d_ptr + object->addr);
		init();
	}
	if (dyn_init_array && dyn_init_arraysz) {
		func_t *init_array = (void*)(dyn_init_array->d_un.d_ptr + object->addr);
		size_t count = dyn_init_arraysz->d_un.d_val / sizeof(func_t);
		for (size_t i=0; i<count; i++) {
			init_array[i]();
		}
	}
}

static void call_destructors(struct elf_object *object) {
	Elf_Dyn *dyn_fini            = find_dynamic(object, DT_FINI);
	Elf_Dyn *dyn_fini_array      = find_dynamic(object, DT_FINI_ARRAY);
	Elf_Dyn *dyn_fini_arraysz    = find_dynamic(object, DT_FINI_ARRAYSZ);
	if (dyn_fini) {
		func_t fini = (void*)(dyn_fini->d_un.d_ptr + object->addr);
		fini();
	}
	if (dyn_fini_array && dyn_fini_arraysz) {
		func_t *fini_array = (void*)(dyn_fini_array->d_un.d_ptr + object->addr);
		size_t count = dyn_fini_arraysz->d_un.d_val / sizeof(func_t);
		for (size_t i=0; i<count; i++) {
			fini_array[i]();
		}
	}
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
	if (dl_debug) fprintf(stderr, "ld-tlibc.so : load elf '%s' at %p\n", path, (void*)object->addr);

	// map segments first
	for (size_t i=0; i<object->phdrs_count; i++) {
		Elf_Phdr *pheader = &object->phdrs[i];
		if (pheader->p_type == PT_DYNAMIC) object->dynamics = (void*)(pheader->p_vaddr + object->addr);
		if (pheader->p_type != PT_LOAD) continue;
		if (map_segment(object, file, pheader) < 0) {
			goto close;
		}
	}

	if (!object->dynamics) {
		dl_error("no PT_DYNAMIC");
		goto close;
	}

	// and now handle the loaded dynamics
	if (handle_dynamics(object) < 0) {
		goto close;
	}

	if (apply_relocs(object) < 0) {
		goto close;
	}
	
	if (set_protections(object) < 0) {
		goto close;
	}
	
	call_constructors(object);
	
	close(file);

	return object;
	
close:
	close(file);
free:
	elf_unload(object);
	return NULL;
}

void elf_unload(struct elf_object *object) {
	call_destructors(object);
	if (object->header.e_type == ET_DYN && object->addr) {
		// we can free the whole allocated block
		munmap((void*)object->addr, get_total_size(object));
	}
	for (size_t i=0; i<object->depencies_count; i++) {
		if (!object->depencies[i]) continue;
		dlclose(object->depencies[i]);
	}
	dl_free(object->depencies);
	dl_free(object->name);
	dl_free(object->phdrs);
	dl_free(object);
}

// taken from the ELF spec
static unsigned long elf_hash(const unsigned char *name) {
	unsigned long h = 0, g;

	while (*name) {
		h = (h << 4) + *name++;
		if ((g = h & 0xf0000000))
			h ^= g >> 24;
		h &= ~g;
	}
	return h;
}

Elf_Sym *elf_lookup(struct elf_object *object, const char *name) {
	uint32_t hash = elf_hash((const unsigned char*)name);
	uint32_t nbucket = object->hash[0];
	uint32_t nchain  = object->hash[1];
	uint32_t *bucket = object->hash + 2;
	uint32_t *chain = object->hash + 2 + nbucket;
	size_t index = bucket[hash % nbucket];
	while (index != 0) {
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
		if (sym->st_shndx != SHN_UNDEF && !strcmp(name, sym_name) && ELF_ST_BIND(sym->st_info) != STB_LOCAL) {
			// we found it
			return sym;
		}

		// go to next entry
		index = chain[index];
	}
	dl_error("symbol not found");
	return NULL;
}
