#include <sysdeps.h>
#include <syscall.h>

int sys_fchdir(int fd) {
	return __set_errno(__syscall1(SYS_fchdir, fd));
}
