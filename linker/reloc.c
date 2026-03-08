#include <elf.h>
#include <string.h>
#include <dlfcn.h>
#include <stdio.h>
#include "linker.h"

#define A rel->r_addend
#define B object->addr
#define P (object->addr + rel->r_offset)
#define S sym->st_value

int reloc(struct elf_object *object, Elf_Rela *rel) {
	size_t sym_index = ELF_R_SYM(rel->r_info);
	Elf_Sym *sym = NULL;
	if (sym_index != 0) {
		if (sym_index >= object->symbols_count) {
			dl_error("invalid symbol index");
			return -1;
		}
		Elf_Sym *obj_sym = &object->symtab[sym_index];
		if (obj_sym->st_shndx == SHN_UNDEF) {
			// the symbol is undefined
			// must link
			const char *name = get_str(object, obj_sym->st_name);
			if (!name) return -1;
			sym = dl_lookup(object, name);
			if (!sym && ELF_ST_BIND(obj_sym->st_info) != STB_WEAK) {
				dl_error("cannot resolve symbol");
				return -1;
			}
			if (!sym) {
				sym = obj_sym;
			}
		} else {
			sym = obj_sym;
		}
	}

	// calculate
	uintptr_t result;
	size_t size;
	switch (ELF_R_TYPE(rel->r_info)) {
#ifdef __x86_64__
	case R_X86_64_NONE:
		return 0;
	case R_X86_64_COPY:
		memcpy((void*)P, (void*)S, sym->st_size);
		return 0;
	case R_X86_64_64:
		size = sizeof(uint64_t);
		result = S + A;
		break;
	case R_X86_64_PC32:
		size = sizeof(uint32_t);
		result = S + A - P;
		break;
	case R_X86_64_GLOB_DAT:
	case R_X86_64_JUMP_SLOT:
		size = sizeof(uint64_t);
		result = S;
		break;
	case R_X86_64_RELATIVE:
		size = sizeof(uint64_t);
		result = B + A;
		break;
	case R_X86_64_32:
	case R_X86_64_32S:
		size = sizeof(uint32_t);
		result = S + A;
		break;
	case R_X86_64_16:
		size = sizeof(uint16_t);
		result = S + A;
		break;
	case R_X86_64_PC16:
		size = sizeof(uint16_t);
		result = S + A - P;
		break;
	case R_X86_64_8:
		size = sizeof(uint8_t);
		result = S + A;
		break;
	case R_X86_64_PC8:
		size = sizeof(uint8_t);
		result = S + A - P;
		break;
	case R_X86_64_PC64:
		size = sizeof(uint64_t);
		result = S + A - P;
		break;
#elif defined(__i386__)
	case R_386_NONE:
		return 0;
	case R_386_32:
		size = sizeof(uint32_t);
		result = S + A;
		break;
	case R_386_PC32:
		size = sizeof(uint32_t);
		result = S + A - P;
		break;
	case R_386_GLOB_DAT:
	case R_386_JMP_SLOT:
		size = sizeof(uint32_t);
		result = S;
		break;
	case R_386_RELATIVE:
		size = sizeof(uint32_t);
		result = B + A;
		break;
#endif
	default:
		return dl_error("unknow relocation type");
	}

	// actually apply
	memcpy((void*)P, &result, size);
	return 0;
}
