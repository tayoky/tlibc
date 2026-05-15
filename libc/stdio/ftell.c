#include <errno.h>
#include <stdio-internal.h>
#include <stdio.h>
#include <unistd.h>

long int ftell(FILE *stream) {
	if (!stream) return __set_errno(-EBADF);
	return lseek(stream->fd, 0, SEEK_CUR);
}
