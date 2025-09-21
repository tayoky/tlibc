#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

FILE *fopen(const char *path,const char *mode){
	int flags = 0;

	if(strchr(mode,'+')){
		flags = O_RDWR;
	}
	switch(mode[0]){
	case 'r':
		if(flags == 0)flags = O_RDONLY;
		break;
	case 'w':
		if(flags == 0)flags = O_WRONLY;
		flags |= O_CREAT | O_TRUNC;
		break;
	case 'a':
		if(flags == 0)flags = O_WRONLY;
		flags |= O_CREAT | O_APPEND;
		break;
	default:
		errno = EINVAL;
		return NULL;
	}

	if(strchr(mode,'e')){
		flags |= O_CLOEXEC;
	}

	int fd = open(path,flags,0777);
	if(fd < 0){
		return NULL;
	}
	
	FILE *stream = fdopen(fd,mode);
	return stream;
}
