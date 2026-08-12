#include <sysdeps.h>

TLIBC_WEAK int sys_tgsigqueue(pid_t pid, pid_t tid, int sig, const union sigval value) {
	if (pid == tid) {
		// try to emulate using sigqueue
		return sys_sigqueue(pid, sig, value);
	} else {
		return SYSDEP_STUB;
	}
}
