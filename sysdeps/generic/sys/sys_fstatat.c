#include <sysdeps.h>

TLIBC_WEAK int sys_fstatat(int fd, const char *restrict path, struct stat *restrict st, int flags) {
	return SYSDEP_STUB;
}
