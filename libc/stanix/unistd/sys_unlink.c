#include <errno.h>
#include <syscall.h>
#include <sysdeps.h>

int sys_unlink(const char *pathname) {
	return __set_errno(__syscall1(SYS_unlink, (long)pathname));
}
