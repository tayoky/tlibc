#include <fcntl.h>
#include <syscall.h>


int open(const char *pathname, int flags, ... /* mode_t mode */ ){
	return __syscall3(SYS_OPEN,(long)pathname,flags,0);
}

int creat(const char *pathname, mode_t mode){
	return __syscall3(SYS_OPEN,(long)pathname,O_CREAT|O_WRONLY|O_TRUNC,mode);
}