#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#undef errno

struct _FILE{
	int fd;
	unsigned long errno;
	int eof;
};

int fseek(FILE *stream, long int offset, int origin){
	if(!stream) return __set_errno(-EBADF);
	stream->eof = 0;
	return __set_errno(lseek(stream->fd,offset,origin));
}

long int ftell(FILE *stream){
	if(!stream) return __set_errno(-EBADF);
	return __set_errno(lseek(stream->fd,0,SEEK_CUR));
}

void rewind(FILE *stream){
	if(!stream){
		__set_errno(-EBADF);
		return;
	}
	stream->errno = 0;
	stream->eof = 0;
	__set_errno(lseek(stream->fd,0,SEEK_SET));
	return;
}