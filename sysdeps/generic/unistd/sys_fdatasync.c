#include <sysdeps.h>

TLIBC_WEAK int sys_fdatasync(int fd) {
	(void)fd;
	return SYSDEP_STUB;
}
