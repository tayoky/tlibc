#include <sysdeps.h>

TLIBC_WEAK int sys_sigsuspend(const sigset_t *mask) {
	return SYSDEP_STUB;
}
