#include <string.h>

size_t strxfrm(char *restrict dest, const char *restrict src, size_t n) {
	// TODO : locale support
	strncpy(dest, src, n);
	return strnlen(dest, n);
}
