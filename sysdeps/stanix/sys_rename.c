#include <errno.h>
#include <sysdeps.h>
#include <syscall.h>

int sys_rename(const char *oldpath, const char *newpath) {
	return __set_errno(__syscall2(SYS_rename, (long)oldpath, (long)newpath));
}
