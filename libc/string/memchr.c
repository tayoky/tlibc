#include <string.h>

void *memchr(const void *buf, int c, size_t count) {
	const char *str = buf;
	while (count-- > 0) {
		if (*str == (char)c) {
			return (void *)str;
		}
		str++;
	}
	return NULL;
}
