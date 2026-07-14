#include <sysdeps.h>

TLIBC_WEAK pid_t sys_getpgid(pid_t pid) {
	return SYSDEP_STUB;
}
