#include <errno.h>
#include <stdio-internal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

ssize_t __fileio_write_unlocked(FILE *stream, const void *buf, size_t count) {
	if (stream->buftype == _IONBF) {
		return __do_write(stream, buf, count);
	}

	// switch to write mode
	if (!stream->write_pos && stream->read_pos) {
		if (fflush(stream) == EOF) return -1;
	}

	// if the write is too big, cut in smaller ones
	size_t total = 0;
	ssize_t ret = 0;
	int need_flush = 0;
	while (count > 0) {
		// not enough place ? flush
		if (stream->write_pos >= stream->write_end) {
			if (stream->write_pos) {
				need_flush = 0;
				size_t pending = stream->write_pos - stream->buf;
				ret = __do_write(stream, stream->buf, pending);
				if (ret < pending) break;
			}
			stream->write_pos = stream->buf;
			stream->write_end = stream->buf + stream->buf_size;
		}

		size_t remaining = stream->write_end - stream->write_pos;
		size_t chunk_size = remaining < count ? remaining : count;
		memcpy(stream->write_pos, buf, chunk_size);
	
		if (stream->buftype == _IOLBF && memchr(stream->write_pos, '\n', chunk_size)) {
			need_flush = 1;
		}

		buf = (char *)buf + chunk_size;
		count -= chunk_size;
		total += chunk_size;
		stream->write_pos += chunk_size;
	}

	if (need_flush) {
		size_t pending = stream->write_pos - stream->buf;
		ret = __do_write(stream, stream->buf, pending);
		stream->write_pos = stream->buf;
		stream->write_end = stream->buf + stream->buf_size;
	}

	if (ret < 0 && total == 0) return ret;
	return total;
}
