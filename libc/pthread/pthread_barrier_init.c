#include <pthread.h>
#include <errno.h>

int pthread_barrier_init(pthread_barrier_t *restrict barrier, const pthread_barrierattr_t *restrict attr, unsigned int count) {
	if (!barrier || count == 0) return EINVAL;
	if (barrier->initalized) return EBUSY;
	barrier->initalized = 1;

	if (attr) {
		barrier->attr = *attr;
	} else {
		pthread_barrierattr_init(&barrier->attr);
	}
	barrier->count = count;

	return 0;
}