#include <sysdeps.h>

TLIBC_WEAK ssize_t sys_read(int fd, void *buffer, size_t count) {
	return SYSDEP_STUB;
}
