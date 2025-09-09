#include <sys/stat.h>
#include <syscall.h>
#include <errno.h>

int lstat(const char *pathname,struct stat *st){
	return __set_errno(__syscall2(SYS_lstat,(long)pathname,(long)st));
}
