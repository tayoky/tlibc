#include <sys/futex.h>
#include <pthread.h>
#include <errno.h>

int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex) {
	if (!cond || !cond->initalized) return EINVAL;

	long seq = atomic_load(&cond->seq) + 1;
	if (mutex) pthread_mutex_unlock(mutex);

	long current = atomic_load(&cond->seq);
	while (seq > current) {
		futex((long*)&cond->seq, FUTEX_WAIT, current);
		current = atomic_load(&cond->seq);
	}
	if (mutex) return pthread_mutex_lock(mutex);
	return 0;
}
