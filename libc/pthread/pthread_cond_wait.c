#include <sysdeps.h>
#include <pthread.h>
#include <errno.h>

int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex) {
	if (!cond || !cond->initalized) return EINVAL;

	futex_val_t seq = atomic_load(&cond->seq) + 1;
	if (mutex) pthread_mutex_unlock(mutex);

	futex_val_t current = atomic_load(&cond->seq);
	while (seq > current) {
		sys_futex_wait(&cond->seq, current);
		current = atomic_load(&cond->seq);
	}
	if (mutex) return pthread_mutex_lock(mutex);
	return 0;
}
