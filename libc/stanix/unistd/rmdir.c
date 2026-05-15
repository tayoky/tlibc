#include <errno.h>
#include <syscall.h>
#include <unistd.h>

int rmdir(const char *pathname) {
	return __set_errno(__syscall1(SYS_rmdir, (long)pathname));
}
