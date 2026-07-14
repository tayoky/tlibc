#include <sysdeps.h>

TLIBC_WEAK int sys_sigwait(const sigset_t *set, int *sig) {
	return __set_errno(-ENOSYS);
}
