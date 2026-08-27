#include <sysdeps.h>

TLIBC_WEAK int sys_fchroot(int fd) {
	(void)fd;
	return SYSDEP_STUB;
}
