#include <signal.h>
#include <unistd.h>
#include <sysdeps.h>

int kill(pid_t pid, int sig) {
	if (sys_kill) {
		return sys_kill(pid, sig);
	} else if (pid == getpid()) {
		// we can try our best
		// NOTE : this is necesarry to make abort
		// work without signal support
		if (sig == SIGKILL || sig == SIGTERM || sig == SIGABRT) {
			_exit(127);
		} else {
			return 0;
		}
	} else {
		return __set_errno(-ENOSYS);
	}
}
