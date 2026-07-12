#include <errno.h>
#include <syscall.h>
#include <unistd.h>

int close(int fd) {
	return __set_errno(__syscall1(SYS_close, (long)fd));
}
