#include <sys/stat.h>
#include <fcntl.h>
#include <sysdeps.h>

#ifndef AT_SYMLINK_NOFOLLOW
#define AT_SYMLINK_NOFOLLOW 0
#endif

int lstat(const char *pathname, struct stat *buf) {
	int ret = sys_lstat(pathname, buf);
#ifdef AT_FDCWD
	if (ret < 0 && errno == ENOSYS) {
		ret = sys_fstatat(AT_FDCWD, pathname, buf, AT_SYMLINK_NOFOLLOW);
	}
#endif
	return ret;
}
