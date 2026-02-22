#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

ssize_t __fileio_read(FILE *stream, void *buf, size_t count) {
	if(!stream){
		return __set_errno(-EBADF);
	}
	size_t total = 0;
	if(count > 0 && stream->unget != EOF){
		*(unsigned char *)buf = (unsigned char)stream->unget;
		stream->unget = EOF;
		buf = (char*)buf + 1;
		count--;
        total++;
	}
	ssize_t rsize = read(stream->fd, buf, count);

	if(rsize < 0){
		stream->error = errno;
		return rsize;
	}

	if((size_t)rsize < count){
		stream->eof = 1;
	}

	total += (size_t)rsize;

	return total;
}