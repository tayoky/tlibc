#include <sysdeps.h>

TLIBC_WEAK int sys_ioctl(int fd, unsigned long op, void *arg) {
	return __set_errno(-ENOSYS);
}
