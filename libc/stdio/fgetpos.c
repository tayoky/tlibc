#include <stdio.h>

int fgetpos(FILE *stream, fpos_t *pos) {
	long off = ftell(stream);
	if (off < 0) return off;
	pos->offset = off;
	return 0;
}
