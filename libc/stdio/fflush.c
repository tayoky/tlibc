#include <stdio-internal.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

extern FILE *__streams;

int fflush(FILE *stream) {
	if (stream == NULL) {
		if (fflush(stdout) == EOF) return EOF;
		if (fflush(stdin)  == EOF) return EOF;
		if (fflush(stderr) == EOF) return EOF;
		stream = __streams;
		while (stream) {
			if (fflush(stream) == EOF) return EOF;
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

	int ret = 0;
	if (stream->write_pos) {
		char *buf = stream->buf;
		size_t count = stream->write_pos - stream->buf;
		while (count > 0) {
			ssize_t w = __do_write(stream, buf, count);
			if (w <= 0) {
				ret = EOF;
				goto error;
			}
			buf += w;
			count -= w;
		}
	} else if (stream->read_pos) {
		// seek back the data we didn't read
		size_t readahead = stream->read_end - stream->read_pos;
		if (lseek(stream->fd, -(off_t)readahead, SEEK_CUR) == (off_t)-1) {
			ret = EOF;
			goto error;
		}
	}

error:
	stream->write_pos = stream->write_end = NULL;
	stream->read_pos  = stream->read_end  = NULL;
	funlockfile(stream);
	return ret;
}
