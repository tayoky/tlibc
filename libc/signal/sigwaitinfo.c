#include <signal.h>
#include <sysdeps.h>

int sigwaitinfo(const sigset_t *restrict set, int *restrict sig, siginfo_t *restrict siginfo) {
	return sys_sigwaitinfo(set, sig, siginfo);
}
