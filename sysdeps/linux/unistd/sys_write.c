#include <sysdeps.h>
#include <sys/syscall.h>
#include <unistd.h>

ssize_t sys_write(int fd, const void *buffer, size_t count) {
	return syscall(SYS_write, fd, buffer, count);
}
