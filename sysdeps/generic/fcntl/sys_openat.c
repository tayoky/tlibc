#include <sysdeps.h>

TLIBC_WEAK int sys_openat(int dirfd, const char *pathname, int flags, mode_t mode) {
	return __set_errno(-ENOSYS);
}
