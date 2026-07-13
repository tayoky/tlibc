#include <sys/stat.h>
#include <sysdeps.h>
#include <errno.h>
#include <syscall.h>

int sys_fstatat(int fd, const char *restrict path, struct stat *restrict st, int flags) {
	return __set_errno(__syscall4(SYS_fstatat, fd, (long)path, (long)st, flags));
}
