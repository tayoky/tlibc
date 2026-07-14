#include <sysdeps.h>

TLIBC_WEAK pid_t sys_waitpid(pid_t pid, int *status, int options) {
	return __set_errno(-ENOSYS);
}
