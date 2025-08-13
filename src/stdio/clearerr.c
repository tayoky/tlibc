#include <stdio.h>

void clearerr(FILE *stream){
	stream->eof = 0;
	stream->errno = 0;
}
