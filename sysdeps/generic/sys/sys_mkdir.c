#include <sysdeps.h>

TLIBC_WEAK int sys_mkdir(const char *pathname, mode_t mode) {
	return __set_errno(-ENOSYS);
}
