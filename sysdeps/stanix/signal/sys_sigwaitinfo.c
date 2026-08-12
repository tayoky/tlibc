#include <syscall.h>
#include <sysdeps.h>

int sys_sigwaitinfo(const sigset_t *restrict set, int *restrict sig, siginfo_t *restrict siginfo) {
	return __set_errno(__syscall3(SYS_sigwaitinfo, (long)set, (long)sig, (long)siginfo));
}
