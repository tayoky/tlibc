#include <sysdeps.h>
#include <unistd.h>

int fdatasync(int fd) {
	return sys_fdatasync(fd);
}
