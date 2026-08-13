#include <sysdeps.h>

TLIBC_WEAK pid_t sys_getsid(void) {
	return SYSDEP_STUB;
}
