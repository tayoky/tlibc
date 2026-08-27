#include <sysdeps.h>
#include <syscall.h>

int fchdir(int fd) {
	return sys_fchdir(fd);
}
