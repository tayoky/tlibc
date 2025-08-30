#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

size_t fwrite(const void *ptr, size_t size, size_t n, FILE *stream){
	if(!stream){
		__set_errno(-EBADF);
		return 0;
	}

	if(stream->buftype == _IONBF){
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

	//if the write is too big, cut in smaller one
	if(size * n > stream->bufsize){
		size_t wsize = size * n;
		while(wsize > 0){
			if(fwrite(ptr,stream->bufsize < wsize ? stream->bufsize : wsize,1,stream) != 1)return (n * size - wsize) / n;
			wsize -= stream->bufsize;
			ptr = (char *)ptr + stream->bufsize;
		}
		return 0;
	}

	//not enough place ? fflush
	if(stream->bufsize - stream->usedsize < size * n){
		if(fflush(stream) < 0)return 0;
	}
	memcpy(&stream->buf[stream->usedsize],ptr,n * size);

	if(memchr(ptr,'\n',n * size)){
		fflush(stream);
	}

	return n;
}
