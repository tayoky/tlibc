#include <sys/stat.h>
#include <fcntl.h>
#include <sysdeps.h>

#ifndef AT_SYMLINK_NOFOLLOW
#define AT_SYMLINK_NOFOLLOW 0
#endif

int lstat(const char *pathname, struct stat *buf) {
	if (sys_lstat) {
		return sys_lstat(pathname, buf);
#ifdef AT_FDCWD
	} else if (sys_fstatat) {
		return sys_fstatat(AT_FDCWD, pathname, buf, AT_SYMLINK_NOFOLLOW);
#endif
	} else if (sys_stat) {
		// technically not correct
		// but most OSes without lstat don't support symlinks
		return sys_stat(pathname, buf);
	} else {
		return __set_errno(-ENOSYS);
	}
}
