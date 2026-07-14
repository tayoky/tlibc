#include <sysdeps.h>

TLIBC_WEAK ssize_t sys_read(int fd, const void *buffer, size_t count) {
	return __set_errno(-ENOSYS);
}
