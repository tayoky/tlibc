#include <sys/ioctl.h>
#include <sysdeps.h>

int ioctl(int fd, unsigned long op, void *arg) {
	return sys_ioctl(fd, op, arg);
}
