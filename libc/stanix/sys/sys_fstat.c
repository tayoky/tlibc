#include <sys/stat.h>
#include <sysdeps.h>
#include <errno.h>
#include <syscall.h>

int sys_fstat(int fd, struct stat *st) {
	return __set_errno(__syscall2(SYS_fstat, (long)fd, (long)st));
}
