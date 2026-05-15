#include <stdio-internal.h>
#include <stdio.h>

int fputc(int lc, FILE *stream) {
	unsigned char c = (unsigned char)lc;
	return __fileio_write(stream, &c, sizeof(c)) > 0 ? lc : EOF;
}
