#include <sysdeps.h>

TLIBC_WEAK int sys_fstat(int fd, struct stat *st) {
	return __set_errno(-ENOSYS);
}
