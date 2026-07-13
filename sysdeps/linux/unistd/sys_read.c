#include <sysdeps.h>
#include <sys/syscall.h>
#include <unistd.h>

ssize_t sys_read(int fd, const void *buffer, size_t count) {
	return syscall(SYS_read, fd, buffer, count);
}
