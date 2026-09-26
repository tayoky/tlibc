#include <stdio-internal.h>

ssize_t __fileio_write(FILE *stream, const void *buf, size_t count)  {
	flockfile(stream);
	ssize_t ret = __fileio_write_unlocked(stream, buf, count);
	funlockfile(stream);
	return ret;
}
