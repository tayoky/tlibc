#include <sysdeps.h>
#include <pthread.h>
#include <limits.h>
#include <errno.h>

int pthread_barrier_wait(pthread_barrier_t *barrier) {
	if (!barrier || !barrier->initalized) return EINVAL;

	futex_val_t id = atomic_fetch_add(&barrier->in, 1) + 1;
	if (id % barrier->count == 0) {
		atomic_store(&barrier->current, id);
		sys_futex_wake(&barrier->current, INT_MAX);
		atomic_fetch_add(&barrier->out, 1);
		return PTHREAD_BARRIER_SERIAL_THREAD;
	}

	futex_val_t current = atomic_load(&barrier->current);
	while (id > current) {
		sys_futex_wait(&barrier->current, current);
		current = atomic_load(&barrier->current);
	}
	atomic_fetch_add(&barrier->out, 1);
	return 0;
}
