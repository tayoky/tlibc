#include <sysdeps.h>

TLIBC_WEAK int sys_truncate(const char *path, off_t length) {
	(void)path;
	(void)length;
	return SYSDEP_STUB;
}
