#include <sysdeps.h>

TLIBC_WEAK int sys_link(const char *oldpath, const char *newpath) {
	return __set_errno(-ENOSYS);
}
