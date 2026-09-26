#include <errno.h>
#include <stdio-internal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

ssize_t __fileio_write_unlocked(FILE *stream, const void *buf, size_t count) {
	if (!stream) {
		return __set_errno(-EBADF);
	}

	if (stream->buftype == _IONBF) {
		return __do_write(stream, buf, count);
	}

	// switch to write mode
	if (!stream->write_pos) {
		if (stream->read_pos) {
			if (fflush(stream) == EOF) return -1;
		}
		stream->write_pos = stream->buf;
		stream->write_end = stream->buf + stream->buf_size;
	}

	// if the write is too big, cut in smaller one
	if (count > stream->buf_size) {
		size_t total = 0;
		while (count > 0) {
			ssize_t w;
			w = __fileio_write(stream, buf, stream->buf_size < count ? stream->buf_size : count);
			if (w < 0) return w;
			if (w == 0) break;
			count -= w;
			buf = (char *)buf + w;
			total += w;
		}
		return total;
	}

	// not enough place ? fflush
	if (stream->write_pos + count > stream->write_end) {
		ssize_t size = stream->write_end - stream->buf;
		if (__do_write(stream, stream->buf, size) < size) {
			return -1;
		}
	}

	memcpy(stream->write_pos, buf, count);
	stream->write_pos += count;

	if (stream->buftype == _IOLBF && memchr(stream->write_pos, '\n', count)) {
		ssize_t size = stream->write_end - stream->buf;
		ssize_t ret = __do_write(stream, stream->buf, size);
		stream->write_pos = stream->buf;
		if (ret < size) return -1;
	}

	return count;
}
