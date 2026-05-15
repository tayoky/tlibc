#include <errno.h>
#include <stdio-internal.h>
#include <stdio.h>
#include <unistd.h>

int fseek(FILE *stream, long int offset, int origin) {
	if (!stream) return __set_errno(-EBADF);
	fflush(stream);
	stream->eof = 0;
	if (lseek(stream->fd, offset, origin) < 0) {
		return -1;
	} else {
		return 0;
	}
}
