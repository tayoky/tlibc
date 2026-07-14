#include <sysdeps.h>

TLIBC_WEAK int sys_stat(const char *pathname, struct stat *st) {
	return __set_errno(-ENOSYS);
}
