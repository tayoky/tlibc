#include <unistd.h>
#include <sysdeps.h>

off_t lseek(int fd, off_t offset, int whence) {
	return sys_lseek(fd, offset, whence);
}
