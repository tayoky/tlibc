#include <sysdeps.h>

TLIBC_WEAK int sys_setpgid(pid_t pid, pid_t pgid) {
	return SYSDEP_STUB;
}
