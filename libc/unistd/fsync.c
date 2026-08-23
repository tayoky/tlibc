#include <sysdeps.h>
#include <unistd.h>

int fsync(int fd) {
	return sys_fsync(fd);
}
