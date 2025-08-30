#include <stdio.h>
#include <fcntl.h>

int __mode2flags(const char *);
FILE *__create_stream(void);

FILE *fopen(const char *path,const char *mode){
	if(!*mode){
		return NULL;
	}

	int flags = __mode2flags(mode);
	if(flags < 0){
		return NULL;
	}

	int fd = open(path,flags);
	if(fd < 0){
		return NULL;
	}
	
	FILE *stream = __create_stream();
	stream->fd = fd;
	return stream;
}
