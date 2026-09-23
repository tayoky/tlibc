#include <stdio-internal.h>
#include <unistd.h>

ssize_t __do_write(FILE *stream, const char *buf, size_t count) {
	ssize_t total = 0;
	while (count > 0) {
		ssize_t ret = write(stream->fd, buf, count);
		if (ret <= 0) {
			stream->error = 1;
			break;
		}
		buf += ret;
		count -= ret;
		total += ret;
	}
	return total;
}
