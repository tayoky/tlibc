#include <signal.h>

int pthread_sigmask(int how, const sigset_t *restrict set, sigset_t *restrict oldset) {
	return sigprocmask(how, set, oldset);
}
