#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

ssize_t __fileio_write(FILE *stream, const void *buf, size_t count) {
	if (!stream) {
		return __set_errno(-EBADF);
	}

	if (stream->buftype == _IONBF) {
		ssize_t wsize = write(stream->fd, buf, count);

		if (wsize < 0) {
			// it's an error
			stream->error = errno;
			return wsize;
		}
		if((size_t)wsize < count){
			stream->eof = 1;
		}
		return wsize;
	}

	// if the write is too big, cut in smaller one
	if (count > stream->bufsize) {
		size_t total = 0;
		while (count > 0) {
			ssize_t w;
			w = __fileio_write(stream, buf, stream->bufsize < count ? stream->bufsize : count);
			if (w < 0) return w;
			if (w == 0) break;
			count -= w;
			buf = (char *)buf + w;
			total += w;
		}
		return total;
	}

	// not enough place ? fflush
	if (stream->bufsize - stream->usedsize < count) {
		if (fflush(stream) < 0) {
			stream->error = errno;
			return -1;
		}
	}
	memcpy(&stream->buf[stream->usedsize], buf, count);

	if (stream->buftype == _IOLBF && memchr(buf, '\n', count)) {
		fflush(stream);
	}

	return count;
}
