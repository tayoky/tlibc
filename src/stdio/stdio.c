#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#undef errno

static FILE _stdin = {
	.fd = 0,
	.errno = 0,
	.eof = 0,
	.unget = EOF,
};
static FILE _stdout = {
	.fd = 1,
	.errno = 0,
	.eof = 0,
	.unget = EOF,
};
static FILE _stderr = {
	.fd = 2,
	.errno = 0,
	.eof = 0,
	.unget = EOF,
};

FILE *stdin = &_stdin;
FILE *stdout = &_stdout;
FILE *stderr = &_stderr;

//TODO : move this to other files

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
	stream->eof = 0;
	stream->unget = EOF;
	return stream;
}


FILE *fdopen(int handle,const char *type){
	(void)type;
	if(handle < 0){
		__set_errno(-EBADF);
		return NULL;
	}

	FILE *stream = malloc(sizeof(FILE));
	stream->errno =0;
	stream->fd = handle;
	stream->eof = 0;
	stream->unget = EOF;

	return stream;
}
