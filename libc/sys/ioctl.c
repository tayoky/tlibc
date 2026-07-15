#include <sys/ioctl.h>
#include <sysdeps.h>
#include <stdarg.h>

int ioctl(int fd, unsigned long op, ...) {
	va_list args;
	va_start(args, op);
	void *arg = va_arg(args, void *);
	va_end(args);
	return sys_ioctl(fd, op, arg);
}
