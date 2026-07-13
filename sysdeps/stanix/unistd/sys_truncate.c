#include <errno.h>
#include <syscall.h>
#include <unistd.h>

int truncate(const char *path, off_t length) {
	return __set_errno(__syscall2(SYS_truncate, (long)path, (long)length));
}
