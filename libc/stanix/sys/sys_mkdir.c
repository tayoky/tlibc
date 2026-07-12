#include <errno.h>
#include <syscall.h>
#include <sysdeps.h>

int sys_mkdir(const char *pathname, mode_t mode) {
	return __set_errno(__syscall2(SYS_mkdir, (long)pathname, (long)mode));
}
