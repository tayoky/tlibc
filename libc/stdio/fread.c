#include <stdio.h>
#include <unistd.h>
#include <errno.h>

ssize_t __fileio_read(FILE *stream, void *buf, size_t count);

size_t fread(void *ptr, size_t size, size_t n, FILE *stream){
	ssize_t r = __fileio_read(stream, ptr, size * n);
	if (r < 0) return 0;
	return r / size;
}
