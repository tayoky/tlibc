#include <string.h>

void *memchr(const void *buf, int c, size_t count) {
	const unsigned char *str = buf;
	while (count-- > 0) {
		if (*str == (unsigned char)c) {
			return (void *)str;
		}
		str++;
	}
	return NULL;
}
