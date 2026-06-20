#include <stdio-internal.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

extern FILE *__streams;

int fflush(FILE *stream) {
	if (stream == NULL) {
		fflush(stdout);
		fflush(stdin);
		fflush(stderr);
		stream = __streams;
		while (stream) {
			fflush(stream);
			stream = stream->next;
		}
		return 0;
	}
	stream->unget = EOF;
	if (stream->buftype == _IONBF || stream->usedsize == 0) return 0;
	char *buf = stream->buf;
	while (stream->usedsize > 0) {
		ssize_t w = write(stream->fd, buf, stream->usedsize);
		if (w < 0) {
			stream->error = errno;
			return -1;
		}
		stream->usedsize -= w;
		buf += w;
	}
	return 0;
}
