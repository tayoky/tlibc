#include <sys/types.h>
#include <stdio.h>

ssize_t __fileio_write(FILE *stream, const void *buf, size_t count);

size_t fwrite(const void *ptr, size_t size, size_t n, FILE *stream){
	ssize_t w = __fileio_write(stream, ptr, size * n);
	if (w < 0) return 0;
	return w / size;
}
