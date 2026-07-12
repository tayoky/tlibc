#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <syscall.h>

int fdname_r(int fd, char *buf, size_t size) {
	return __set_errno(__syscall3(SYS_fdname, fd, (long)buf, size));
}

char *fdname(int fd) {
	static char buf[256];
	return fdname_r(fd, buf, sizeof(buf)) < 0 ? NULL : buf;
}
