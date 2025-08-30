#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int setvbuf(FILE *stream, char *buf, int type, size_t size){
	if(!stream) return __set_errno(-EBADF);

	fflush(stream);
	if(type != _IONBF){
		if(!buf && !size) size = BUFSIZ;
		if(!buf) buf = malloc(size);
	}

	//do we free old buffer ?
	stream->buftype = type;
	stream->bufsize = size;
	stream->buf      = buf;

	return 0;
}
