#include <sys/stat.h>
#include <syscall.h>
#include <errno.h>

int stat(const char *pathname,struct stat *st){
	return __set_errno(__syscall2(SYS_stat,(long)pathname,(long)st));
}
