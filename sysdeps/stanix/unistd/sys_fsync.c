#include <syscall.h>
#include <sysdeps.h>

int sys_fsync(int fd) {
	return __set_errno(__syscall1(SYS_fsync, fd));
}
