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
	if (stream->buftype == _IONBF || !stream->write_pos) return 0;
	char *buf = stream->buf;
	size_t count = stream->write_pos - stream->buf;
	while (count > 0) {
		ssize_t w = __do_write(stream, buf, count);
		if (w <= 0) return EOF;
		buf += w;
	}
	stream->write_pos = stream->write_end = NULL;
	stream->read_pos  = stream->read_end  = NULL;
	return 0;
}
