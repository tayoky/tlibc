#include <sysdeps.h>

TLIBC_WEAK int sys_sigqueue(pid_t pid, int sig, const union sigval value) {
	(void)pid;
	(void)sig;
	(void)value;
	return SYSDEP_STUB;
}
