#include <sysdeps.h>

TLIBC_WEAK int sys_ftruncate(int fd, off_t length) {
	(void)fd;
	(void)length;
	return SYSDEP_STUB;
}
