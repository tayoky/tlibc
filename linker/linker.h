#ifndef LINKER_H
#define LINKER_H

#include <limits.h>
#include <stdint.h>
#include <stddef.h>
#include <elf.h>

#ifdef BITS32
#define Elf_Ehdr Elf32_Ehdr
#define Elf_Phdr Elf32_Phdr
#define Elf_Shdr Elf32_Shdr
#define Elf_Addr Elf32_Addr
#define Elf_Sym  Elf32_Sym
#define Elf_Dyn  Elf32_Dyn
#define Elf_Rela Elf32_Rela
#define Elf_Rel  Elf32_Rel
#define Elf_Auxv Elf32_Auxv
#define ELF_R_SYM(i)  ELF32_R_SYM(i)
#define ELF_R_TYPE(i) ELF32_R_TYPE(i)
#define ELF_R_INFO(i) ELF32_R_INFO(i)
#define ELF_ST_BIND(i) ELF32_ST_BIND(i)
#define ELF_ST_TYPE(i) ELF32_ST_TYPE(i)
#define ELF_ST_INFO(b,t) ELF32_ST_INFO(b,t)
#define ELFCLASS ELFCLASS32
#else
#define Elf_Ehdr Elf64_Ehdr
#define Elf_Phdr Elf64_Phdr
#define Elf_Shdr Elf64_Shdr
#define Elf_Addr Elf64_Addr
#define Elf_Sym  Elf64_Sym
#define Elf_Dyn  Elf64_Dyn
#define Elf_Rela Elf64_Rela
#define Elf_Rel  Elf64_Rel
#define Elf_Auxv Elf64_Auxv
#define ELF_R_SYM(i)  ELF64_R_SYM(i)
#define ELF_R_TYPE(i) ELF64_R_TYPE(i)
#define ELF_R_INFO(i) ELF64_R_INFO(i)
#define ELF_ST_BIND(i) ELF64_ST_BIND(i)
#define ELF_ST_TYPE(i) ELF64_ST_TYPE(i)
#define ELF_ST_INFO(b,t) ELF64_ST_INFO(b,t)
#define ELFCLASS ELFCLASS64
#endif

typedef void (*func_t)(void);

struct elf_table {
	void *ptr;
	size_t size;
};

struct elf_object {
	struct elf_object *next;
	struct elf_object *prev;
	struct elf_object *global_next;
	struct elf_object *global_prev;
	Elf_Ehdr header;
	size_t ref_count;
	uintptr_t addr;
	char *name;
	Elf_Phdr *phdrs;
	char *strtab;
	Elf_Sym *symtab;
	Elf_Dyn *dynamics;
	uint32_t *hash;
	struct elf_object **deps;
	void *tls;
	size_t phdrs_count;
	size_t strtab_size;
	size_t symbols_count;
	size_t hash_size;
	size_t deps_count;
	size_t id;
	size_t tls_filesz;
	size_t tls_size;
	int flags;
	int state;
};

#define STATE_LOADED          0
#define STATE_DYNAMICS_PARSED 1
#define STATE_RELOCATED       2
#define STATE_READY           3

struct tls_index {
	unsigned long ti_module;
	unsigned long ti_offset;
};
void *__tls_get_addr(struct tls_index *ti);

struct lookup {
	const char *name;
	uint32_t hash;
	Elf_Sym *found_sym;
	struct elf_object *found_object;
	int skip_program;
};

void dl_setup_libc_alloc(void);
void *dl_alloc(size_t size);
void dl_free(void *ptr);
char *dl_strdup(const char *str);
char *dl_strndup(const char *str, size_t count);
int dl_error(char *str);
struct elf_object *dl_load(const char *filename, int fd, int flags);
int dl_relocate(struct elf_object *object);
int dl_finish_loading(struct elf_object *object);
void dl_unload(struct elf_object *object);
void lookup_init(struct lookup *lookup, const char *name);
int lookup_object(struct lookup *lookup, struct elf_object *object);
int lookup_deps(struct lookup *lookup, struct elf_object *object);
int lookup_global(struct lookup *lookup);

struct elf_object *elf_load(const char *path, int lib, int fd);
int elf_handle_dynamics(struct elf_object *object);
int elf_relocate(struct elf_object *object);
int elf_constructors(struct elf_object *object);
int elf_destructors(struct elf_object *object);
void elf_unload(struct elf_object *object);
Elf_Sym *elf_lookup(struct lookup *lookup, struct elf_object *object);

void abi_enter(void *entry, long *auxv, size_t auxv_size);
struct elf_object *cache_find_id(size_t id);
int open_lib(const char *path);
const char *get_str(struct elf_object *object, size_t offset);
int reloc(struct elf_object *object, Elf_Rela *rel);

extern const char *lib_path;
extern const char *rpath;
extern int dl_debug;

#ifndef PAGE_SIZE
#define PAGE_SIZE 4096
#endif

#define PAGE_ALIGN_DOWN(addr) ((addr) / PAGE_SIZE * PAGE_SIZE)
#define PAGE_ALIGN_UP(addr) (((addr) + PAGE_SIZE - 1)/ PAGE_SIZE * PAGE_SIZE)

#endif
