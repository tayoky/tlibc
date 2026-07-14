#include <sysdeps.h>

TLIBC_WEAK int sys_chmod(const char *pathname, mode_t mode) {
	return SYSDEP_STUB;
}
