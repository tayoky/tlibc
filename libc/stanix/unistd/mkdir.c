#include <unistd.h>
#include <syscall.h>
#include <errno.h>

int mkdir(const char *pathname,mode_t mode){
	return __set_errno(__syscall2(SYS_mkdir,(long)pathname,(long)mode));
}
