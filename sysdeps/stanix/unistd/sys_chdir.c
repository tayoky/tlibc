#include <sysdeps.h>
#include <syscall.h>

int sys_chdir(const char *path) {
	return __set_errno(__syscall1(SYS_chdir, (long)path));
}
