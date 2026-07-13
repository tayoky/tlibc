#include <signal.h>

int sigemptyset(sigset_t *sigset) {
	*sigset = 0;
	return 0;
}
