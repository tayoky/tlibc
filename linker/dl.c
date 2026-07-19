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
static struct elf_object *global_first = NULL;
static struct elf_object *global_last = NULL;
static struct elf_object *program = NULL;
const char *lib_path = NULL;
const char *rpath = NULL;
int dl_debug = 0;
struct elf_object ld_tlibc = {
	.ref_count = 1,
	.flags = RTLD_GLOBAL,
	.state = STATE_READY,
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

struct elf_object *cache_find_id(size_t id) {
	struct elf_object *cur = cache_first;
	while (cur) {
		if (cur->id == id) {
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

static void global_add(struct elf_object *object) {
	object->global_prev = global_last;
	object->global_next = NULL;
	if (global_last) {
		global_last->global_next = object;
	} else {
		global_first = object;
	}
	global_last = object;
}

static void global_remove(struct elf_object *object) {
	if (object->global_prev) {
		object->global_prev->global_next = object->global_next;
	} else {
		global_first = object->global_next;
	}

	if (object->global_next) {
		object->next->global_prev = object->global_prev;
	} else {
		global_last = object->global_prev;
	}
}

int dl_error(char *str) {
	error_string = str;
	return -1;
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

static Elf_Sym *self_lookup(const char *name) {
	static Elf_Sym sym = {
		.st_info = ELF_ST_INFO(STB_GLOBAL, STT_FUNC),
	};
	if (!strcmp(name, "environ")) {
		sym.st_value = (uintptr_t)(void *)&environ;
		sym.st_size = sizeof(environ);
		return &sym;
	}
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
	if (!strcmp(name, "__tls_get_addr")) {
		sym.st_value = (uintptr_t)(void *)__tls_get_addr;
		return &sym;
	}
	return NULL;
}

void lookup_init(struct lookup *lookup, const char *name) {
	lookup->name = name;
	lookup->hash = elf_hash((const unsigned char *)name);
	lookup->found_sym = NULL;
	lookup->found_object = NULL;
	lookup->skip_program = 0;
}

int lookup_object(struct lookup *lookup, struct elf_object *object) {
	if (lookup->skip_program && object == program) return 0;
	Elf_Sym *sym;
	if (object == &ld_tlibc) {
		sym = self_lookup(lookup->name);
	} else {
		sym = elf_lookup(lookup, object);
	}
	if (!sym) return 0;
	
	// the only case where we can override is
	// overriding weak with global
	if (!lookup->found_sym || (ELF_ST_BIND(lookup->found_sym->st_info) == STB_WEAK && ELF_ST_BIND(sym->st_info) == STB_GLOBAL)) {
		lookup->found_sym = sym;
		lookup->found_object = object;
		return 1;
	}
	return 0;
}

int lookup_deps(struct lookup *lookup, struct elf_object *object) {
	int found = 0;
	for (size_t i=0; i<object->deps_count; i++) {
		found = lookup_object(lookup, object->deps[i]) || found;
	}
	return found;
}

int lookup_global(struct lookup *lookup) {
	int found = 0;
	for (struct elf_object *object = global_first; object; object = object->global_next) {
		found = lookup_object(lookup, object) || found;
	}
	return found;
}

struct elf_object *dl_load(const char *filename, int fd, int flags) {
	const char *name = strchr(filename, '/');
	if (name) {
		name++;
	} else {
		name = filename;
	}
	
	struct elf_object *object = cache_find(name);
	if (object) {
		object->ref_count++;
		if (!(object->flags & RTLD_GLOBAL) && (flags & RTLD_GLOBAL)) {
			object->flags |= RTLD_GLOBAL;
			global_add(object);
		}
		return object;
	}
	if (flags & RTLD_NOLOAD) return NULL;
	object = elf_load(filename, 1, fd);
	if (!object) return NULL;

	object->name = dl_strdup(name);
	object->ref_count = 1;
	object->flags = flags;
	object->state = STATE_LOADED;
	cache_add(object);
	if (flags & RTLD_GLOBAL) {
		global_add(object);
	}

	if (elf_handle_dynamics(object) < 0) {
		dl_unload(object);
		return NULL;
	}
	object->state = STATE_DYNAMICS_PARSED;
	return object;
}

int dl_relocate(struct elf_object *object) {
	if (object->state >= STATE_RELOCATED) return 0;
	for (size_t i=0; i<object->deps_count; i++) {
		if (dl_relocate(object->deps[i]) < 0) return -1;
	}
	if (elf_relocate(object) < 0) return -1;
	object->state = STATE_RELOCATED;
	return 0;
}

int dl_finish_loading(struct elf_object *object) {
	if (object->state >= STATE_READY) return 0;
	for (size_t i=0; i<object->deps_count; i++) {
		if (dl_finish_loading(object->deps[i]) < 0) return -1;
	}
	if (elf_constructors(object) < 0) return -1;
	object->state = STATE_READY;
	return 0;
}
	
void dl_unload(struct elf_object *object) {
	if (object->ref_count-- > 1) return;
	if (object->state >= STATE_READY) {
		elf_destructors(object);
	}
	if (object->flags & RTLD_GLOBAL) {
		global_remove(object);
	}
	cache_remove(object);
	elf_unload(object);
}

void *dlopen(const char *filename, int flags) {
	if (!(flags & (RTLD_LAZY | RTLD_NOW))) {
		dl_error("invalid flags");
		return NULL;
	}
	if (!filename) {
		return program;
	}

	struct elf_object *object = dl_load(filename, flags, -1);
	if (!object) return NULL;
	if (dl_relocate(object) < 0) goto unload;
	if (dl_finish_loading(object) < 0) goto unload;
	return object;

unload:
	dl_unload(object);
	return NULL;
}

int dlclose(void *handle) {
	struct elf_object *object = handle;
	if (object == program
		|| handle == RTLD_DEFAULT
		|| handle == RTLD_NEXT) {
		return 0;
	}
	if (!object) return dl_error("Invalid object");
	dl_unload(object);
	return 0;
}

char *dlerror(void) {
	char *ret = error_string;
	error_string = NULL;
	return ret;
}

void *dlsym(void *handle, const char *sym) {
	struct lookup lookup;
	int found = 0;
	lookup_init(&lookup, sym);
	if (handle == RTLD_DEFAULT) {
		found = lookup_global(&lookup);
	} else if (handle == RTLD_NEXT) {
		// TODO
		return NULL;
	} else {
		found = lookup_object(&lookup, handle);
		found = lookup_deps(&lookup, handle) || found;
	}
	
	return found ? (void *)lookup.found_sym->st_value + lookup.found_object->addr : NULL;
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
	global_add(&ld_tlibc);

	// maybee the kernel gave us a fd for the executable
	errno = 0;
	int fd = (int)getauxval(AT_EXECFD);
	if (fd == 0 && errno == ENOENT) fd = -1;

	program = dl_load(argv[0], fd, RTLD_GLOBAL | RTLD_NOW);
	if (!program) {
error:
		fprintf(stderr, "ld-tlibc.so : %s\n", dlerror());
		return EXIT_FAILURE;
	}
	if (dl_relocate(program) < 0) goto error;
	if (dl_finish_loading(program) < 0) goto error;

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
