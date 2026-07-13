#include <signal.h>
#include <sysdeps.h>

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact) {
	return CALL_SYSDEP(sys_sigaction, (signum, act, oldact));
}
