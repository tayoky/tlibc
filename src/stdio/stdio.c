#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#undef errno

struct _FILE{
	int fd;
	unsigned long errno;
};

static FILE _stdin = {
	.fd = 0,
	.errno = 0
};
static FILE _stdout = {
	.fd = 1,
	.errno = 0
};
static FILE _stderr = {
	.fd = 2,
	.errno = 0
};

FILE *stdin = &_stdin;
FILE *stdout = &_stdout;
FILE *stderr = &_stderr;

static int mode2flags(const char *mode){
	int flags = 0;
	//we don't care about binary of text mode
	
	if(mode[1] == '+' || (mode[1] && mode[2] == '+')){
		//both read an write
		flags |= O_RDWR;
	}

	switch (mode[0])
	{
	case 'r':
		break;
	case 'w':
		flags |= O_TRUNC;
		flags |= O_CREAT;
		if(!(flags & O_RDWR)){
			flags |= O_WRONLY;
		}
		break;
	case 'a':
		flags |= O_APPEND;
		flags |= O_CREAT;
		if(!(flags & O_RDWR)){
			flags |= O_WRONLY;
		}
		break;
	default:
		return -1;
		break;
	}

	return flags;
}

FILE *fopen(const char *path,const char *mode){
	if(!*mode){
		return NULL;
	}

	int flags = mode2flags(mode);
	if(flags < 0){
		return NULL;
	}

	int fd = open(path,flags);
	if(fd < 0){
		return NULL;
	}
	
	FILE *stream = malloc(sizeof(FILE));
	stream->fd = fd;
	stream->errno = 0;
	return stream;
}

int fclose(FILE *stream){
	if(!stream)return __set_errno(-EBADF);

	close(stream->fd);
	free(stream);
	return 0;
}

size_t fread(void * ptr, size_t size, size_t n, FILE *stream){
	if(!stream)return __set_errno(-EBADF);

	ssize_t rsize = read(stream->fd,ptr,size * n);

	if(rsize < 0){
		//it's an error
		stream->errno = errno;
		return 0;
	}

	return (size_t)rsize;
}

size_t fwrite(void * ptr, size_t size, size_t n, FILE *stream){
	if(!stream)return __set_errno(-EBADF);

	ssize_t wsize = write(stream->fd,ptr,size * n);

	if(wsize < 0){
		//it's an error
		stream->errno = errno;
		return 0;
	}

	return (size_t)wsize;
}

int fprintf(FILE *stream, const char *fmt, ...){
	va_list args;
	va_start(args,fmt);
	int ret = vfprintf(stream,fmt,args);
	va_end(args);
	return ret;
}

int vfprintf(FILE *stream, const char *fmt, va_list args){
	if(!stream)return __set_errno(-EBADF);

	char buf[PRINTF_MAX];
	buf[PRINTF_MAX - 1] ='\0';
	vsnprintf(buf,PRINTF_MAX,fmt,args);

	//find the size of the buffer;
	size_t bufsize = PRINTF_MAX;
	if(buf[PRINTF_MAX - 1] == '\0'){
		bufsize = strlen(buf);
	}

	return fwrite(buf,bufsize,1,stream);
}

int printf(const char *fmt, ...){
	va_list args;
	va_start(args, fmt);
	int ret = vprintf(fmt,args);
	va_end(args);
	return ret;
}

int vprintf(const char *fmt, va_list args){
	return vfprintf(stdout,fmt,args);
}

FILE *fdopen(int handle, char *type){
	if(handle < 0){
		return __set_errno(handle);
	}

	FILE *stream = malloc(sizeof(FILE));
	stream->errno =0;
	stream->fd = handle;

	return stream;
}