#include <sysdeps.h>
#include <pthread.h>
#include <limits.h>
#include <errno.h>

int pthread_cond_broadcast(pthread_cond_t *cond) {
	if (!cond || !cond->initalized) return EINVAL;

	atomic_fetch_add(&cond->seq, 1);
	sys_futex_wake(&cond->seq, INT_MAX);

	return 0;
}
