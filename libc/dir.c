#include <unistd.h>
#include <syscall.h>
#include <fcntl.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

struct _DIR {
	int fd;
	long int offset;
	struct dirent ret;
};

DIR *opendir(const char *pathname){
	int fd = open(pathname,O_DIRECTORY);
	if(fd < 0){
		return NULL;
	}

	DIR *dir = malloc(sizeof(DIR));
	dir->fd = fd;
	dir->offset = 0;
	return dir;
}

int closedir(DIR *dir){
	if(dir == NULL){
		return __set_errno(-EBADF);
	}
	if(close(dir->fd)>=0){
		free(dir);
		return -1;
	}
	
	return 0;
}

struct dirent *readdir(DIR *dir){
	if(dir == NULL){
		__set_errno(-EBADF);
		return NULL;
	}

	//stupid POSIX api ...
	//there are no function for the raw readdir syscall
	int old_errno = errno;
	if(__set_errno(__syscall3(SYS_readdir,dir->fd,(long)&dir->ret,(long)dir->offset)) < 0){
		//hitting end (no more entry) should not trigger an errno
		if(errno == ENOENT) errno = old_errno;
		return NULL;
	}
	
	dir->offset++;

	//NOTE : the next time readdir is used the previous result is lost
	return &dir->ret;
}

void seekdir(DIR *dir,long int offset){
	if(dir == NULL){
		__set_errno(-EBADF);
		return;
	}
	dir->offset = offset;
}

long int telldir(DIR *dir){
	if(dir == NULL){
		return __set_errno(-EBADF);
	}
	return dir->offset;
}

void rewinddir(DIR *dir){
	return seekdir(dir,0);
}
