#include <sys/futex.h>
#include <pthread.h>
#include <limits.h>
#include <errno.h>

int pthread_barrier_wait(pthread_barrier_t *barrier) {
	if (!barrier || !barrier->initalized) return EINVAL;

	long id = atomic_fetch_add(&barrier->in, 1) + 1;
	if (id % barrier->count == 0) {
		atomic_store(&barrier->current, id);
		futex((long*)&barrier->current, FUTEX_WAKE, INT_MAX);
		atomic_fetch_add(&barrier->out, 1);
		return PTHREAD_BARRIER_SERIAL_THREAD;
	}

	long current = atomic_load(&barrier->current);
	while (id > current) {
		futex((long*)&barrier->current, FUTEX_WAIT, current);
		current = atomic_load(&barrier->current);
	}
	atomic_fetch_add(&barrier->out, 1);
	return 0;
}
