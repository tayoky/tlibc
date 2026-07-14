#include <sysdeps.h>

TLIBC_WEAK int sys_sigaction(int signum, const struct sigaction *act, struct sigaction *oldact) {
	return SYSDEP_STUB;
}
