#include <signal.h>
#include <errno.h>

int sigaddset(sigset_t *sigset, int signum) {
	if (signum <= 0 || signum >= NSIG) return __set_errno(-EINVAL);
	*sigset |= sigmask(signum);
	return 0;
}
