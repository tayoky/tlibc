#include <errno.h>
#include <fcntl.h>
#include <sysdeps.h>
#include <syscall.h>

int sys_open(const char *pathname, int flags, mode_t mode) {
	return __set_errno(__syscall3(SYS_open, (long)pathname, flags, mode));
}
