#include <stdio-internal.h>
#include <unistd.h>

ssize_t __do_read(FILE *stream, char *buf, size_t count) {
	ssize_t r = read(stream->fd, buf, count);
	if (r < 0) {
		stream->error = 1;
		return r;
	}

	if ((size_t)r < count) {
		stream->eof = 1;
	}
	return r;
}
