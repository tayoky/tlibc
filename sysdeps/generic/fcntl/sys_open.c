#include <sysdeps.h>
#include <fcntl.h>

TLIBC_WEAK int sys_open(const char *pathname, int flags, mode_t mode) {
#ifdef AT_FDCWD
	return sys_openat(AT_FDCWD, pathname, flags, mode);
#else
	return __set_errno(-ENOSYS);
#endif
}
