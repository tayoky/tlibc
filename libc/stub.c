#include <stdio.h>

#define STUB(name) \
	int name() { \
		fprintf(stderr, "tlibc : STUB " #name " was called\n"); \
		return 0; \
	}

STUB(utime)
STUB(clock)
STUB(alarm)
STUB(popen)
STUB(pclose)
STUB(sched_yield)

STUB(pthread_cond_init)
STUB(pthread_cond_destroy)
STUB(pthread_cond_broadcast)
STUB(pthread_cond_signal)
STUB(pthread_cond_timedwait)
STUB(pthread_cond_wait)
STUB(pthread_detach)
STUB(pthread_cancel)
