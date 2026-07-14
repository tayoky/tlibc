#include <sysdeps.h>

TLIBC_WEAK pid_t sys_fork(void) {
	return __set_errno(-ENOSYS);
}
