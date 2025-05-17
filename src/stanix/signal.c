#include <signal.h>

int sigaddset(sigset_t *sigset, int signum){
	*sigset |= sigmask(signum);
	return 0;
}

int sigdelset(sigset_t *sigset, int signum){
	*sigset &= ~sigmask(signum);
	return 0;
}

int sigemptyset(sigset_t *sigset){
	*sigset = 0;
	return 0;
}

int sigfillset(sigset_t *sigset){
	*sigset = (sigset_t)(-1);
	return 0;
}