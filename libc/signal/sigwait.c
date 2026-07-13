#include <signal.h>
#include <sysdeps.h>

int sigwait(const sigset_t *set, int *sig) {
	return CALL_SYSDEP(sys_sigwait, (set, sig));
}
