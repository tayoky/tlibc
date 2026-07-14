#include <sysdeps.h>

TLIBC_WEAK int sys_fchmod(int fd, mode_t mode) {
	return SYSDEP_STUB;
}
