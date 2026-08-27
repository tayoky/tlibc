#include <sysdeps.h>
#include <syscall.h>

int fchroot(int fd) {
	return sys_fchroot(fd);
}
