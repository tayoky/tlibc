#include <pthread.h>
#include <errno.h>

int pthread_barrier_destroy(pthread_barrier_t *barrier) {
	if (!barrier || !barrier->initalized) return EINVAL;
	barrier->initalized = 0;
	return 0;
}
