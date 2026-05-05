#include <stdio.h>
#include <stdio-internal.h>

int ferror(FILE *stream){
	return stream->error;
}
