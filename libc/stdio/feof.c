#include <stdio-internal.h>
#include <stdio.h>

int feof(FILE *stream) {
	flockfile(stream);
	int eof = stream->eof;
	funlockfile(stream);
	return eof;
}
