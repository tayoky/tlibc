#include <sysdeps.h>

TLIBC_WEAK int sys_kill(pid_t pid, int sig) {
	if (pid == sys_getpid()) {
		// we can try our best
		// NOTE : this is necesarry to make abort
		// work without signal support
		if (sig == SIGKILL || sig == SIGTERM || sig == SIGABRT) {
			sys_exit(127);
			for(;;);
		} else {
			return 0;
		}
	} else {
		return SYSDEP_STUB;
	}
}
