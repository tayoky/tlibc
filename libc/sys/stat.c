#include <sys/stat.h>
#include <fcntl.h>
#include <sysdeps.h>

int stat(const char *pathname, struct stat *buf) {
	int ret = sys_stat(pathname, buf);
#ifdef AT_FDCWD
	if (ret < 0 && errno == ENOSYS) {
		ret = sys_fstatat(AT_FDCWD, pathname, buf, 0);
	}
#endif
	return ret;
}
