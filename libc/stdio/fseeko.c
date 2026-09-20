#include <stdio-internal.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int fseeko(FILE *stream, off_t offset, int origin) {
	if (!stream) return __set_errno(-EBADF);
	fflush(stream);
	stream->eof = 0;
	if (lseek(stream->fd, offset, origin) < 0) {
		return -1;
	} else {
		return 0;
	}
}
