#include <fcntl.h>
#include <syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *pathname, int flags, ... /* mode_t mode */ ){
	//get the mode if open
	mode_t mode = 0;
	if(flags & O_CREAT){
		va_list args;
		va_start(args,flags);
		mode = va_arg(args,mode_t);
		va_end(args);
	}
	return __set_errno(__syscall3(SYS_open,(long)pathname,flags,mode));
}

int creat(const char *pathname, mode_t mode){
	return __set_errno(__syscall3(SYS_open,(long)pathname,O_CREAT|O_WRONLY|O_TRUNC,mode));
}

int fcntl(int fd, int op, ... /* arg */ ){
	int arg = 0;
	if(op == F_SETFD || op == F_DUPFD){
		va_list args;
		va_start(args,op);
		arg = va_arg(args,int);
		va_end(args);
	}
	
	return __set_errno(__syscall3(SYS_fcntl,fd,op,arg));
}
