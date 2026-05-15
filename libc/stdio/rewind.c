#include <errno.h>
#include <stdio-internal.h>
#include <stdio.h>
#include <unistd.h>

void rewind(FILE *stream) {
	if (!stream) return (void)__set_errno(-EBADF);
	fflush(stream);
	stream->error = 0;
	stream->eof = 0;
	lseek(stream->fd, 0, SEEK_SET);
	return;
}
