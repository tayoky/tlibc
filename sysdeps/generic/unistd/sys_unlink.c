#include <sysdeps.h>

TLIBC_WEAK int sys_unlink(const char *pathname) {
	return __set_errno(-ENOSYS);
}
