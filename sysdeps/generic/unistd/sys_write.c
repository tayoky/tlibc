#include <sysdeps.h>

TLIBC_WEAK ssize_t sys_write(int fd, const void *buffer, size_t count) {
	return __set_errno(-ENOSYS);
}
