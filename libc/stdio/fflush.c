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
	flockfile(stream);
	stream->unget = EOF;
	if (stream->buftype == _IONBF) {
		funlockfile(stream);
		return 0;
	}

	if (stream->write_pos) {
		char *buf = stream->buf;
		size_t count = stream->write_pos - stream->buf;
		while (count > 0) {
			ssize_t w = __do_write(stream, buf, count);
			if (w <= 0) {
				funlockfile(stream);
				return EOF;
			}
			buf += w;
		}
	} else if (stream->read_pos) {
		// seek back the data we didn't read
		size_t readahead = stream->read_end - stream->read_pos;
		lseek(stream->fd, SEEK_CUR, -readahead);
	}
	stream->write_pos = stream->write_end = NULL;
	stream->read_pos  = stream->read_end  = NULL;
	funlockfile(stream);
	return 0;
}
