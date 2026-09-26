#include <stdio-internal.h>

int getc_unlocked(FILE *stream) {
	unsigned char c = 0;
	return __fileio_read_unlocked(stream, &c, sizeof(c)) > 0 ? c : EOF;
}
