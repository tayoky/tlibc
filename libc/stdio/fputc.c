#include <stdio.h>
#include <stdio-internal.h>

int fputc(int lc, FILE *stream) {
	unsigned char c = (unsigned char)lc;
	return __fileio_write(stream, &c, sizeof(c)) > 0 ? lc : EOF;
}
