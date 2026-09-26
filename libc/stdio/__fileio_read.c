#include <stdio-internal.h>

ssize_t __fileio_read(FILE *stream, void *buf, size_t count) {
	flockfile(stream);
	ssize_t ret = __fileio_read_unlocked(stream, buf, count);
	funlockfile(stream);
	return ret;
}
