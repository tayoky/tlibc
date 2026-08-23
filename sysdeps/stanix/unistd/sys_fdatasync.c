#include <syscall.h>
#include <sysdeps.h>

int sys_fdatasync(int fd) {
	return __set_errno(__syscall1(SYS_fdatasync, fd));
}
