#include <errno.h>
#include <syscall.h>
#include <unistd.h>

int chdir(const char *path) {
	return __set_errno(__syscall1(SYS_chdir, (long)path));
}
