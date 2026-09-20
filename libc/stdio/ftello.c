#include <stdio-internal.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

off_t ftello(FILE *stream) {
	if (!stream) return __set_errno(-EBADF);
	return lseek(stream->fd, 0, SEEK_CUR);
}
