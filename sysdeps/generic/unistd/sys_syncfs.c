#include <sysdeps.h>

TLIBC_WEAK int sys_syncfs(int fd) {
	(void)fd;
	return SYSDEP_STUB;
}
