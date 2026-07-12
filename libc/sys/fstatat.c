#include <sys/stat.h>
#include <fcntl.h>
#include <sysdeps.h>

int fstatat(int fd, const char *restrict pathname, struct stat *restrict buf, int flags) {
	if (sys_fstatat) {
		return sys_fstatat(fd, pathname, buf, flags);
#ifdef AT_FDCWD
#ifdef AT_SYMLINK_NOFOLLOW
	} else if (sys_lstat && fd == AT_FDCWD && (flags & AT_SYMLINK_NOFOLLOW)) {
		// we can try our best using lstat
		return sys_lstat(pathname, buf);
#endif
	} else if (sys_stat && fd == AT_FDCWD) {
		// we can try our best using stat
		return sys_stat(pathname, buf);
#endif
	} else {
		return __set_errno(-ENOSYS);
	}
}
