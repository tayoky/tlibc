#include <sysdeps.h>

TLIBC_WEAK int sys_chdir(const char *path) {
	(void)path;
	return SYSDEP_STUB;
}
