#include <signal.h>
#include <sysdeps.h>

sighandler_t signal(int signum, sighandler_t handler) {
	if (sys_signal) {
		return sys_signal(signum, handler);
	} else if (sys_sigaction) {
		struct sigaction action = {
			.sa_handler = handler,
			.sa_flags = 0,
			.sa_mask = 0,
		};

		struct sigaction old;

		if (sys_sigaction(signum, &action, &old) < 0) {
			return SIG_ERR;
		}

		return old.sa_handler;
	} else {
		__set_errno(-ENOSYS);
		return SIG_ERR;
	}
}
