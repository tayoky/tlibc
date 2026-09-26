#include <stdio-internal.h>
#include <stdio.h>

int ferror(FILE *stream) {
	flockfile(stream);
	int error = stream->error;
	funlockfile(stream);
	return error;
}
