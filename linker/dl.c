#include <sys/auxv.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "linker.h"

// the dynamic linker of tlibc

static char *error_string = NULL;
static struct elf_object *cache_last = NULL;
static struct elf_object *cache_first = NULL;
static struct elf_object *program = NULL;
const char *lib_path = NULL;
const char *rpath = NULL;
int dl_debug = 0;
struct elf_object ld_tlibc = {
	.ref_count = 1,
};

static struct elf_object *cache_find(const char *name) {
	struct elf_object *cur = cache_first;
	while (cur) {
		if (!strcmp(cur->name, name)) {
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}

static void cache_add(struct elf_object *object) {
	object->prev = cache_last;
	object->next = NULL;
	if (cache_last) {
		cache_last->next = object;
	} else {
		cache_first = object;
	}
	cache_last = object;
}

static void cache_remove(struct elf_object *object) {
	if (object->prev) {
		object->prev->next = object->next;
	} else {
		cache_first = object->next;
	}

	if (object->next) {
		object->next->prev = object->prev;
	} else {
		cache_last = object->prev;
	}
}

int dl_error(char *str) {
	error_string = str;
	return -1;
}

void *dlopen(const char *filename, int flags) {
	if (!(flags & (RTLD_LAZY | RTLD_NOW))) {
		dl_error("invalid flags");
		return NULL;
	}
	if (!filename) {
		return program;
	}
	const char *name = strchr(filename, '/');
	if (name) {
		name++;
	} else {
		name = filename;
	}
	struct elf_object *object = cache_find(filename);
	if (object) {
		object->ref_count++;
		if (flags & RTLD_NOLOAD) {
			// we can use NOLOAD to update flags
			object->flags = flags;
		}
		return object;
	}
	if (flags & RTLD_NOLOAD) return NULL;

	object = elf_load(filename, 1, -1);
	if (!object) return NULL;

	object->name = dl_strdup(name);
	object->ref_count = 1;
	object->flags = flags;
	cache_add(object);
	return object;
}

int dlclose(void *handle) {
	struct elf_object *object = handle;
	if (!object) return dl_error("Invalid object");
	if (object == program
		|| handle == RTLD_DEFAULT
		|| handle == RTLD_NEXT) {
		return 0;
	}
	object->ref_count--;
	if (object->ref_count > 0) return 0;
	cache_remove(object);
	elf_unload(object);
	return 0;
}

char *dlerror(void) {
	char *ret = error_string;
	error_string = NULL;
	return ret;
}

static Elf_Sym *self_lookup(const char *name) {
	static Elf_Sym sym = {
		.st_info = ELF_ST_INFO(STB_GLOBAL, STT_FUNC),
	};
	if (!strcmp(name, "dlopen")) {
		sym.st_value = (uintptr_t)(void *)dlopen;
		return &sym;
	}
	if (!strcmp(name, "dlclose")) {
		sym.st_value = (uintptr_t)(void *)dlclose;
		return &sym;
	}
	if (!strcmp(name, "dlsym")) {
		sym.st_value = (uintptr_t)(void *)dlsym;
		return &sym;
	}
	if (!strcmp(name, "dlerror")) {
		sym.st_value = (uintptr_t)(void *)dlerror;
		return &sym;
	}
	return NULL;
}

Elf_Sym *dl_lookup(struct elf_object *object, const char *name, int flags, struct elf_object **found_object) {
	Elf_Sym *sym = NULL;
	// lookup ourself only if not asking for depencies
	if (!(flags & LOOKUP_DEPENCIES)) {
		if (object == &ld_tlibc) {
			sym = self_lookup(name);
		} else {
			sym = elf_lookup(object, name);
		}
		if (found_object) *found_object = object;
	}
	for (size_t i = 0; i < object->depencies_count; i++) {
		struct elf_object *new_object;
		Elf_Sym *new_sym = dl_lookup(object->depencies[i], name, flags & ~LOOKUP_DEPENCIES, &new_object);
		if (!new_sym) continue;
		// better than what we found ?
		// global overwrite weak
		if (!sym || (ELF_ST_BIND(new_sym->st_info) == STB_GLOBAL && ELF_ST_BIND(sym->st_info) == STB_WEAK)) {
			sym = new_sym;
			if (found_object) *found_object = new_object;
		}
	}
	return sym;
}

void *dlsym(void *handle, const char *sym) {
	if (handle == RTLD_DEFAULT) {
		// first try the executable
		Elf_Sym *ret = elf_lookup(program, sym);
		if (ret) return (void *)(ret->st_value + program->addr);
		// all library marked as global
		struct elf_object *lib = cache_first;
		while (lib) {
			if (lib->flags & RTLD_GLOBAL) {
				ret = elf_lookup(lib, sym);
				if (ret) return (void *)(ret->st_value + lib->addr);
			}
			lib = lib->next;
		}
		return NULL;
	}
	if (handle == RTLD_NEXT) {
		// TODO
		return NULL;
	}
	if (!handle) return NULL;
	struct elf_object *object = handle;
	struct elf_object *found_object;
	Elf_Sym *ret = dl_lookup(object, sym, 0, &found_object);
	return ret ? (void *)ret->st_value + found_object->addr : NULL;
}

static const char *auxv_name(long type) {
	switch (type) {
	case AT_NULL:
		return "AT_NULL";
	case AT_IGNORE:
		return "AT_IGNORE";
	case AT_EXECFD:
		return "AT_EXECFD";
	case AT_PHDR:
		return "AT_PHDR";
	case AT_PHENT:
		return "AT_PHENT";
	case AT_PHNUM:
		return "AT_PHNUM";
	case AT_PAGESZ:
		return "AT_PAGESZ";
	case AT_BASE:
		return "AT_BASE";
	case AT_FLAGS:
		return "AT_FLAGS";
	case AT_ENTRY:
		return "AT_ENTRY";
	case AT_NOTELF:
		return "AT_NOTELF";
	case AT_UID:
		return "AT_UID";
	case AT_EUID:
		return "AT_EUID";
	case AT_GID:
		return "AT_GID";
	case AT_EGID:
		return "AT_EGID";
	case AT_PLATFORM:
		return "AT_PLATFORM";
	case AT_HWCAP:
		return "AT_HWCAP";
	case AT_CLKTCK:
		return "AT_CLKTCK";
	case AT_SECURE:
		return "AT_SECURE";
	case AT_BASE_PLATFORM:
		return "AT_BASE_PLATFORM";
	case AT_RANDOM:
		return "AT_RANDOM";
	case AT_HWCAP2:
		return "AT_HWCAP2";
	case AT_EXECFN:
		return "AT_EXECFN";
	default:
		return "AT_???";
	}
}

int main(int argc, char **argv, char **envp) {
	const char *progname = strrchr(argv[0], '/');
	if (progname) {
		// remove the slash
		progname++;
	} else {
		progname = argv[0];
	}
	if (!strcmp(progname, "ld-tlibc.so")) {
		// the dynamic linker can be called as an executable
		if (argc < 2) {
			puts("usage : ld-tlibc.so PROGRAM [ARGUMENT]...");
			puts("or    : ld-tlibc.so OPTION");
			return EXIT_FAILURE;
		}
		if (!strcmp(argv[1], "--help")) {
			puts("usage : ld-tlibc.so PROGRAM [ARGUMENT]...");
			puts("or    : ld-tlibc.so OPTION");
			puts("launch a dynamic linked program");
			return 0;
		}
		// shift args
		argc--;
		argv++;
	}
	if (getuid() == geteuid() && getgid() == getegid()) {
		// don't allow LD_LIBRARY_PATH or LD_DEBUG on set-uid/gid programs
		lib_path = getenv("LD_LIBRARY_PATH");
		const char *ld_debug = getenv("LD_DEBUG");
		dl_debug = ld_debug && ld_debug[0];

		if (getenv("LD_SHOW_AUXV")) {
			long *auxv = (long *)envp;

			// jump over envp
			while (*auxv) auxv++;
			auxv++;

			Elf_Auxv *entry = (Elf_Auxv *)auxv;
			while (entry->a_type != AT_NULL) {
				fprintf(stderr, "%s: %ld\n", auxv_name(entry->a_type), entry->a_un.a_val);
				entry++;
			}
		}
	}

	// add the linker itself to the cache
	ld_tlibc.name = "ld-tlibc.so",
	cache_add(&ld_tlibc);

	// maybee the kernel gave us a fd for the executable
	errno = 0;
	int fd = (int)getauxval(AT_EXECFD);
	if (fd == 0 && errno == ENOENT) fd = -1;

	program = elf_load(argv[0], 0, fd);
	if (!program) {
		fprintf(stderr, "ld-tlibc.so : %s\n", dlerror());
		return EXIT_FAILURE;
	}

	dl_setup_libc_alloc();

	int envc = 0;
	while (envp[envc]) {
		envc++;
	}

	long *auxv_top = (long *)envp;
	while (*auxv_top) auxv_top++;
	auxv_top++;
	while (*auxv_top) auxv_top++;
	long *auxv = (long *)argv;
	auxv--;

	// align the size
	size_t auxv_size = auxv_top - auxv;
	if (auxv_size % 2) {
		auxv_size++;
	}

	// emulate entry from kernel
	abi_enter((void *)(program->header.e_entry + program->addr), auxv, auxv_size * sizeof(long));
	return EXIT_FAILURE;
}
