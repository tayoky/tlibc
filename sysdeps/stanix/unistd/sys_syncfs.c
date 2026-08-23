#include <syscall.h>
#include <sysdeps.h>

int sys_syncfs(int fd) {
	return __set_errno(__syscall1(SYS_syncfs, fd));
}
