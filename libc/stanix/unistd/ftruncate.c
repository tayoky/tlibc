#include <errno.h>
#include <syscall.h>
#include <unistd.h>

int ftruncate(int fd, off_t length) {
	return __set_errno(__syscall2(SYS_ftruncate, fd, (long)length));
}
