#include <sys/stat.h>
#include <fcntl.h>
#include <sysdeps.h>

int fstatat(int fd, const char *restrict pathname, struct stat *restrict buf, int flags) {
	int ret = sys_fstatat(fd, pathname, buf, flags);
	if (ret >= 0 || errno != ENOSYS) return ret;
#ifdef AT_FDCWD
#ifdef AT_SYMLINK_NOFOLLOW
	if (fd == AT_FDCWD && (flags & AT_SYMLINK_NOFOLLOW)) {
		// we can try our best using lstat
		ret = sys_lstat(pathname, buf);
		if (ret >= 0 || errno != ENOSYS) return ret;
	}
#endif
	if (fd == AT_FDCWD) {
		// we can try our best using stat
		ret = sys_stat(pathname, buf);
		if (ret >= 0 || errno != ENOSYS) return ret;
	}
#endif
	return __set_errno(-ENOSYS);
}
