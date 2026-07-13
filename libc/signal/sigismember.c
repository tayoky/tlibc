#include <signal.h>
#include <errno.h>

int sigismember(const sigset_t *set, int signum) {
	if (signum <= 0 || signum >= NSIG) return __set_errno(-EINVAL);
	return !!(*set & sigmask(signum));
}
