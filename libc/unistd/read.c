#include <unistd.h>
#include <sysdeps.h>

ssize_t read(int fd, const void *buffer, size_t count) {
	return sys_read(fd, buffer, count);
}
