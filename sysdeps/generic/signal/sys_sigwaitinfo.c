#include <sysdeps.h>

TLIBC_WEAK int sys_sigwaitinfo(const sigset_t *restrict set, int *restrict sig, siginfo_t *restrict siginfo) {
	(void)set;
	(void)sig;
	(void)siginfo;
	return SYSDEP_STUB;
}
