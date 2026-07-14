#include <sysdeps.h>

TLIBC_WEAK sighandler_t sys_signal(int signum, sighandler_t handler) {
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
}
