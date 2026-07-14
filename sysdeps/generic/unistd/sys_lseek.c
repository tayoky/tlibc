#include <sysdeps.h>

TLIBC_WEAK off_t sys_lseek(int fd, off_t offset, int whence) {
	return __set_errno(-ENOSYS);
}
