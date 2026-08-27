#include <sysdeps.h>
#include <syscall.h>

int sys_fchroot(int fd) {
	return __set_errno(__syscall1(SYS_fchroot, fd));
}
