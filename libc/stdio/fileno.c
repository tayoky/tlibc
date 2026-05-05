#include <stdio.h>
#include <stdio-internal.h>

int fileno(FILE *stream){
	return stream->fd;
}
