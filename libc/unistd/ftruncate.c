#include <sysdeps.h>
#include <unistd.h>

int ftruncate(int fd, off_t length) {
	return sys_ftruncate(fd, length);
}
