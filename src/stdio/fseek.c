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
	fflush(stream);
	stream->eof = 0;
	if(lseek(stream->fd,offset,origin) < 0){
		return -1;
	} else {
		return 0;
	}
}

long int ftell(FILE *stream){
	if(!stream) return __set_errno(-EBADF);
	return lseek(stream->fd,0,SEEK_CUR);
}

void rewind(FILE *stream){
	if(!stream) return (void)__set_errno(-EBADF);
	fflush(stream);
	stream->errno = 0;
	stream->eof = 0;
	lseek(stream->fd,0,SEEK_SET);
	return;
}
