#include <errno.h>
#include <stdio.h>
#include <syscall.h>

int rename(const char *oldpath, const char *newpath) {
	return __set_errno(__syscall2(SYS_rename, (long)oldpath, (long)newpath));
}
