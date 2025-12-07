#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int setvbuf(FILE *stream, char *buf, int type, size_t size){
	if (!stream) return __set_errno(-EBADF);
	if (type > _IOLBF) return __set_errno(-EINVAL);

	fflush(stream);
	if (type == _IONBF) {
		size = 0;
	} else {
		if(!buf && !size) size = BUFSIZ;
	}

	if (size != stream->bufsize || buf) {
		if (stream->internalbuf) free(stream->buf);
		stream->bufsize = size;
		if (!size) {
			stream->buf = NULL;
			stream->internalbuf = 0;
		} else if (buf) {
			stream->buf = buf;
			stream->internalbuf = 0;
		} else {
			stream->buf = malloc(size);
			stream->internalbuf = 1;
		}
	}

	stream->buftype = type;

	return 0;
}
