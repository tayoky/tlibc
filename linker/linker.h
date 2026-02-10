#ifndef LINKER_H
#define LINKER_H

#include <limits.h>
#include <elf.h>

#ifdef BITS32
#define Elf_Ehdr Elf32_Ehdr
#define Elf_Phdr Elf32_Phdr
#define Elf_Shdr Elf32_Shdr
#define Elf_Addr Elf32_Addr
#define Elf_Sym  Elf32_Sym
#define Elf_Dyn  Elf32_Dyn
#define Elf_Rela Elf32_Rela
#define ELF_R_SYM(i)  ELF32_R_SYM(i)
#define ELF_R_TYPE(i) ELF32_R_TYPE(i)
#define ELF_R_INFO(i) ELF32_R_INFO(i)
#define ELFCLASS ELFCLASS32
#else
#define Elf_Ehdr Elf64_Ehdr
#define Elf_Phdr Elf64_Phdr
#define Elf_Shdr Elf64_Shdr
#define Elf_Addr Elf64_Addr
#define Elf_Sym  Elf64_Sym
#define Elf_Dyn  Elf64_Dyn
#define Elf_Rela Elf64_Rela
#define ELF_R_SYM(i)  ELF64_R_SYM(i)
#define ELF_R_TYPE(i) ELF64_R_TYPE(i)
#define ELF_R_INFO(i) ELF64_R_INFO(i)
#define ELFCLASS ELFCLASS64
#endif

struct elf_object {
	struct elf_object *next;
	struct elf_object *prev;
	Elf_Ehdr header;
	int fd;
	size_t ref_count;
	uintptr_t addr;
	char *name;
	Elf_Phdr *phdr;
	Elf_Dyn  *dynamics;
	char *strtab;
	Elf_Sym *symtab;
	size_t phdr_count;
	size_t dynamics_count;
};

void dl_setup_libc_alloc(void);
void *dl_alloc(size_t size);
void dl_free(void *ptr);
char *dl_strdup(const char *str);
int dl_error(char *str);
struct elf_object *elf_load(const char *path);
void elf_unload(struct elf_object *object);
void *elf_lookup(struct elf_object *object, const char *name);

#ifndef PAGE_SIZE
#define PAGE_SIZE 4096
#endif

#define PAGE_ALIGN_DOWN(addr) ((addr) / PAGE_SIZE * PAGE_SIZE)

#endif
