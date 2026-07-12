#include <sys/stat.h>
#include <fcntl.h>
#include <sysdeps.h>

int stat(const char *pathname, struct stat *buf) {
	if (sys_stat) {
		return sys_stat(pathname, buf);
#ifdef AT_FDCWD
	} else if (sys_fstatat) {
		return sys_fstatat(AT_FDCWD, pathname, buf, 0);
#endif
	} else {
		return __set_errno(-ENOSYS);
	}
}
