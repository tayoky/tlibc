#include <sys/stat.h>
#include <errno.h>
#include <syscall.h>

int chmod(const char *pathname, mode_t mode) {
	return __set_errno(__syscall2(SYS_chmod, (long)pathname, mode));
}
