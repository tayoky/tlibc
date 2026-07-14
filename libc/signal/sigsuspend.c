#include <signal.h>
#include <sysdeps.h>

int sigsuspend(const sigset_t *mask) {
	return sys_sigsuspend(mask);
}
