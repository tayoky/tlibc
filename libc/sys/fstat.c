#include <sys/stat.h>
#include <sysdeps.h>

int fstat(int fd, struct stat *buf) {
	return sys_fstat(fd, buf);
}
