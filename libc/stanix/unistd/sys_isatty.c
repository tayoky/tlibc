#include <errno.h>
#include <syscall.h>
#include <sysdeps.h>

int sys_isatty(int fd) {
	int ret = __syscall1(SYS_isatty, (long)fd);
	// isatty is a bit diferent as it should return 0 and not -1;
	if (ret < 0) {
		errno = -ret;
		return 0;
	}

	return ret;
}
