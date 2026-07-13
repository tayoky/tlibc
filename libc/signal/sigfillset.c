#include <signal.h>

int sigfillset(sigset_t *sigset) {
	*sigset = (sigset_t)(-1UL);
	return 0;
}
