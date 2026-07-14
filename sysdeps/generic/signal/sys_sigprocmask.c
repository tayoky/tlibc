#include <sysdeps.h>

TLIBC_WEAK int sys_sigprocmask(int how, const sigset_t *set, sigset_t *oldset) {
	return __set_errno(-ENOSYS);
}
