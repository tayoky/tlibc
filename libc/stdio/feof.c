#include <stdio.h>
#include <stdio-internal.h>

int feof(FILE *stream){
	return stream->eof;
}
