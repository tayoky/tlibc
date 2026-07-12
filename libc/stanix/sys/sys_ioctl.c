#include <sysdeps.h>
#include <errno.h>
#include <syscall.h>

int sys_ioctl(int fd, unsigned long op, void *arg) {
	return __set_errno(__syscall3(SYS_ioctl, fd, op, (long)arg));
}
