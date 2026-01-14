#include <sys/types.h>
#include <stdio.h>

ssize_t __fileio_write(FILE *stream, const void *buf, size_t count);

int fputc(int lc, FILE *stream) {
	unsigned char c = (unsigned char)lc;
	return __fileio_write(stream, &c, sizeof(c)) > 0 ? lc : EOF;
}
