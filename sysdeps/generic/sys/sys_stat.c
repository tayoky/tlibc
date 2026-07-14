#include <sysdeps.h>
#include <fcntl.h>

TLIBC_WEAK int sys_stat(const char *pathname, struct stat *buf) {
#ifdef AT_FDCWD
	return sys_fstatat(AT_FDCWD, pathname, buf, 0);
#else
	return __set_errno(-ENOSYS);
#endif
}
