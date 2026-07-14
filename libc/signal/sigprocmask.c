#include <signal.h>
#include <sysdeps.h>

int sigprocmask(int how, const sigset_t *set, sigset_t *oldset) {
	return sys_sigprocmask(how, set, oldset);
}
