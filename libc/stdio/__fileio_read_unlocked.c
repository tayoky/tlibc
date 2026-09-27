#include <errno.h>
#include <stdio-internal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

ssize_t __fileio_read_unlocked(FILE *stream, void *buf, size_t count) {
	ssize_t total = 0;
	if (count > 0 && stream->unget != EOF) {
		*(unsigned char *)buf = (unsigned char)stream->unget;
		stream->unget = EOF;
		buf = (char *)buf + 1;
		count--;
		total++;
	}

	ssize_t ret = 0;
	if (stream->buftype == _IONBF) {
		ret = __do_read(stream, buf, count);
		if (ret > 0) total += ret;
	} else {
		// switch to read mode
		if (!stream->read_pos && stream->write_pos) {
			if (fflush(stream) == EOF) return -1;
		}

		// if the read is too big, cut in smaller ones
		while (count > 0) {
			if (stream->read_pos >= stream->read_end) {
				// no more data to read
				// refill buffer
				ret = __do_read(stream, stream->buf, stream->buf_size);
				if (ret <= 0) break;
				stream->read_pos = stream->buf;
				stream->read_end = stream->buf + ret;
			}
			size_t readahead = stream->read_end - stream->read_pos;
			size_t chunk_size = readahead < count ? readahead : count;

			memcpy(buf, stream->buf, chunk_size);
			buf = (char *)buf + chunk_size;
			count -= chunk_size;
			total += chunk_size;
			stream->read_pos += chunk_size;
		}
	}

	if (ret < 0 && total == 0) return ret;
	return total;
}
