#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <limits.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <elf.h>
#include "linker.h"

// the dynamic linker of tlibc

static char *error_string = NULL;
static struct elf_object *cache_last = NULL;
static struct elf_object *cache_first = NULL;
static struct elf_object *program = NULL;
const char *lib_path = NULL;

static struct elf_object *cache_find(const char *name) {
	struct elf_object *cur = cache_first;
	while (cur) {
		if (!strcmp(cur->name, name)) {
			return cur;
		}
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

void *dlopen(const char *filename ,int flags) {
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
		return object;
	}
	if (flags & RTLD_NOLOAD) return NULL;

	object = elf_load(filename);
	if (!object) return NULL;

	object->name      = dl_strdup(name);
	object->ref_count = 1;
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

void *dlsym(void *handle, const char *sym) {
	if (handle == RTLD_DEFAULT) {
		// TODO
		return NULL;
	}
	if (handle == RTLD_NEXT) {
		// TODO
		return NULL;
	}
	struct elf_object *object = handle;
	return elf_lookup(object, sym);
}

int main(int argc, char **argv, char **envp) {
	if(argc < 2){
		puts("usage : ld.so PROGRAM [ARGUMENT]...");
		puts("or    : ld.so OPTION");
		return EXIT_FAILURE;
	}
	if(!strcmp(argv[1],"--help")){
		puts("usage : ld.so PROGRAM [ARGUMENT]...");
		puts("or    : ld.so OPTION");
		puts("launch a dynamic linked program");
		return 0;
	}
	if (getuid() == geteuid() && getgid() == getegid()) {
		// don't allow LD_LIBRARY_PATH on set-uid/gid programs
		lib_path = getenv("LD_LIBRARY_PATH");
	}

	program = elf_load(argv[1]);
	if (!program) return EXIT_FAILURE;

	dl_setup_libc_alloc();

	int envc = 0;
	while (envp[envc]) {
		envc++;
	}

	// emulate entry from kernel
	abi_enter((void*)program->header.e_entry, argc, argv, 0, envp);
	return EXIT_FAILURE;
}
