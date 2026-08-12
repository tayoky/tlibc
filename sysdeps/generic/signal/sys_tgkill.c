#include <sysdeps.h>

TLIBC_WEAK int sys_tgkill(pid_t pid, pid_t tid, int sig) {
	if (pid == tid) {
		// emulate using kill
		return sys_kill(pid, sig);
	} else {
		return SYSDEP_STUB;
	}
}
