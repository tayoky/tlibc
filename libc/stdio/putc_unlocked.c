#include <stdio-internal.h>

int putc_unlocked(int lc, FILE *stream) {
	unsigned char c = (unsigned char)lc;
	return __fileio_write_unlocked(stream, &c, sizeof(c)) > 0 ? lc : EOF;
}
