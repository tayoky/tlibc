#include <unistd.h>
#include <sysdeps.h>

ssize_t write(int fd, const void *buffer, size_t count) {
	return sys_write(fd, buffer, count);
}
