#include <sys/stat.h>
#include <syscall.h>
#include <errno.h>

int fstat(int fd,struct stat *st){
	return __set_errno(__syscall2(SYS_fstat,(long)fd,(long)st));
}
