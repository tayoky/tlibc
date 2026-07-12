#include <sys/stat.h>
#include <sysdeps.h>
#include <errno.h>
#include <syscall.h>

int sys_stat(const char *pathname, struct stat *st) {
	return __set_errno(__syscall2(SYS_stat, (long)pathname, (long)st));
}
