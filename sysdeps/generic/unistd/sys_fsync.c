#include <sysdeps.h>

TLIBC_WEAK int sys_fsync(int fd) {
	(void)fd;
	return SYSDEP_STUB;
}
