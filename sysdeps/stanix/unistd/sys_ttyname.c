#include <fcntl.h>
#include <sysdeps.h>

// the stanix kernel provide a very usefull fdname syscall

int sys_ttyname_r(int fd, char *buf, size_t size) {
	return fdname_r(fd, buf, size);
}
