#include <string.h>
#include <stddef.h>
#include <dlfcn.h>
#include "linker.h"


static void *(*_malloc)(size_t size) = NULL;
static void (*_free)(void *ptr) = NULL;
static char early_buf[4096];
static size_t early_ptr = 0;

void dl_setup_libc_alloc(void) {
	// setup libc allocator
	void *libc = dlopen("libc.so", 0);
	_malloc = dlsym(libc, "malloc");
	_free   = dlsym(libc, "free");
}

void *dl_alloc(size_t size) {
	if (_malloc) return _malloc(size);
	if (early_ptr + size >= sizeof(early_buf)) {
		// the early buf is full
		return NULL;
	}
	char *ptr = early_buf + early_ptr;
	early_ptr += size;
	return ptr;
}

void dl_free(void *ptr) {
	if ((char*)ptr >= early_buf && (char*)ptr < early_buf + sizeof(early_buf)) return;
	if (_free) _free(ptr);
}

char *dl_strdup(const char *str) {
	char *dup = dl_alloc(strlen(str) + 1);
	if (!dup) return NULL;
	return strcpy(dup, str);
}
