#include <sysdeps.h>

TLIBC_WEAK int sys_fchdir(int fd) {
	(void)fd;
	return SYSDEP_STUB;
}
