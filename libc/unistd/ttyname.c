#include <unistd.h>
#include <limits.h>
#include <sysdeps.h>

int ttyname_r(int fd, char *buf, size_t size) {
	return sys_ttyname_r(fd, buf, size);
}

char *ttyname(int fd) {
	static char buf[PATH_MAX];
	return ttyname_r(fd, buf, sizeof(buf)) >= 0 ? buf : NULL;
}
