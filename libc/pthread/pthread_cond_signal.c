#include <sys/futex.h>
#include <pthread.h>
#include <limits.h>
#include <errno.h>

int pthread_cond_signal(pthread_cond_t *cond) {
	if (!cond || !cond->initalized) return EINVAL;

	atomic_fetch_add(&cond->seq, 1);
	futex((long*)&cond->seq, FUTEX_WAKE, 1);
	return 0;
}
