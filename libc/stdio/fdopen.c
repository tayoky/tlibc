#include <stdio.h>
#include <errno.h>

FILE *__create_stream(void);

FILE *fdopen(int handle,const char *type){
	(void)type;
	if(handle < 0){
		__set_errno(-EBADF);
		return NULL;
	}

	FILE *stream = __create_stream();
	if(!stream)return NULL;
	stream->fd = handle;
	setvbuf(stream, NULL, _IOFBF, 0);

	return stream;
}
