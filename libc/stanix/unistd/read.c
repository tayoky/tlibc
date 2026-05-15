#include <errno.h>
#include <syscall.h>
#include <unistd.h>

ssize_t read(int fd, const void *buffer, size_t count) {
	return __set_errno(__syscall3(SYS_read, fd, (long)buffer, count));
}
