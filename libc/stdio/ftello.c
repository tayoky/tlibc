#include <stdio-internal.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

off_t ftello(FILE *stream) {
	if (!stream) return __set_errno(-EBADF);
	flockfile(stream);
	off_t offset = lseek(stream->fd, 0, SEEK_CUR);
	if (offset >= 0) {
		if (stream->write_pos) {
			offset += stream->write_pos - stream->buf;
		} else {
			offset -= stream->read_end - stream->read_pos;
		}
	}
	funlockfile(stream);
	return offset;
}
