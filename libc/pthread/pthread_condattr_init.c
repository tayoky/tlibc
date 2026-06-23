#include <errno.h>
#include <pthread.h>

int pthread_condattr_init(pthread_condattr_t *condattr) {
	if (!condattr) return EINVAL;
	condattr->pshared = PTHREAD_PROCESS_PRIVATE;
	condattr->clock_id = CLOCK_MONOTONIC;
	return 0;
}
