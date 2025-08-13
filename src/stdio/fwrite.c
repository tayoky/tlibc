#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>

size_t fwrite(const void *ptr, size_t size, size_t n, FILE *stream){
	if(!stream){
		__set_errno(-EBADF);
		return 0;
	}

	ssize_t wsize = write(stream->fd,ptr,size * n);

	if(wsize < 0){
		//it's an error
		stream->errno = errno;
		return 0;
	}

	if((size_t)wsize < size * n){
		stream->eof = 1;
	}

	return ((size_t)wsize) / size;
}
