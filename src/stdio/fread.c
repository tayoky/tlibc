#include <stdio.h>
#include <unistd.h>
#include <errno.h>

size_t fread(void * ptr, size_t size, size_t n, FILE *stream){
	if(!stream){
		__set_errno(-EBADF);
		return 0;
	}
	size_t r = 0;
	size_t size2read = size * n;
	if(size2read > 0 && stream->unget != EOF){
		*(unsigned char *)ptr = (unsigned char)stream->unget;
		stream->unget = EOF;
		(char *)ptr ++;
		size2read--;
		r++;
	}
	ssize_t rsize = read(stream->fd,ptr,size2read);

	if(rsize < 0){
		//it's an error
		stream->error = errno;
		return 0;
	}

	if((size_t)rsize < size * n){
		stream->eof = 1;
	}

	r+= (size_t)rsize;

	return r/ size;
}
