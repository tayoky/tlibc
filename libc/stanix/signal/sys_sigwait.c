#include <syscall.h>
#include <sysdeps.h>

int sys_sigwait(const sigset_t *set, int *sig) {
	return __set_errno(__syscall2(SYS_sigwait, (long)set, (long)sig));
}
