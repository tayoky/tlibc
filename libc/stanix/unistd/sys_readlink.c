#include <errno.h>
#include <syscall.h>
#include <unistd.h>

ssize_t readlink(const char *path, char *buf, size_t bufsize) {
	return __set_errno(__syscall3(SYS_readlink, (long)path, (long)buf, bufsize));
}
