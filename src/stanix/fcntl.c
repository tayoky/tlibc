#include <fcntl.h>
#include <syscall.h>
#include <stdarg.h>


int open(const char *pathname, int flags, ... /* mode_t mode */ ){
	//get the mode if open
	mode_t mode = 0;
	if(flags & O_CREAT){
		va_list args;
		va_start(args,flags);
		mode = va_arg(args,mode_t);
		va_end(args);
	}
	return __syscall3(SYS_OPEN,(long)pathname,flags,mode);
}

int creat(const char *pathname, mode_t mode){
	return __syscall3(SYS_OPEN,(long)pathname,O_CREAT|O_WRONLY|O_TRUNC,mode);
}