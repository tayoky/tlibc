#include <unistd.h>
#include <syscall.h>
#include <errno.h>

int access(const char *pathname, int mode){
	return __set_errno(__syscall2(SYS_access,(long)pathname,mode));
}
