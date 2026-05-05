#include <stdio.h>
#include <stdio-internal.h>

void clearerr(FILE *stream){
	stream->eof = 0;
	stream->error = 0;
}
