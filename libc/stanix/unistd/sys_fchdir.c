#include <errno.h>
#include <syscall.h>
#include <unistd.h>

int fchdir(int fd) {
	return __set_errno(__syscall1(SYS_fchdir, fd));
}
