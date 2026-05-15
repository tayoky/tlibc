#include <errno.h>
#include <syscall.h>
#include <unistd.h>

int link(const char *oldpath, const char *newpath) {
	return __set_errno(__syscall2(SYS_link, (long)oldpath, (long)newpath));
}
