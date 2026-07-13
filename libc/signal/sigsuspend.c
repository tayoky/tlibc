#include <signal.h>
#include <sysdeps.h>

int sigsuspend(const sigset_t *mask) {
	return CALL_SYSDEP(sys_sigsuspend, (mask));
}
