#include <sys/stat.h>
#include <errno.h>
#include <syscall.h>

int fchmod(int fd, mode_t mode) {
	return __set_errno(__syscall2(SYS_fchmod, fd, mode));
}
