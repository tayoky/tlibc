#include <sysdeps.h>

TLIBC_WEAK int sys_chroot(const char *path) {
	(void)path;
	return SYSDEP_STUB;
}
