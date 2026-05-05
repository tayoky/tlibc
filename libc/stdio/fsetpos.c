#include <stdio.h>

int fsetpos(FILE *stream, fpos_t *pos) {
	return fseek(stream, pos->offset, SEEK_SET);
}
