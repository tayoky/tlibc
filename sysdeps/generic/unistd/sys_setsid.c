#include <sysdeps.h>

TLIBC_WEAK pid_t sys_setsid(void) {
	return SYSDEP_STUB;
}
