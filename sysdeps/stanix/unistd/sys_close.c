#include <errno.h>
#include <syscall.h>
#include <sysdeps.h>

int sys_close(int fd) {
	return __set_errno(__syscall1(SYS_close, (long)fd));
}
