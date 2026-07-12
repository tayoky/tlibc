#include <errno.h>
#include <syscall.h>
#include <sysdeps.h>

ssize_t sys_read(int fd, const void *buffer, size_t count) {
	return __set_errno(__syscall3(SYS_read, fd, (long)buffer, count));
}
