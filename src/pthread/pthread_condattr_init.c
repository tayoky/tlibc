#include <pthread.h>
#include <errno.h>

int pthread_condattr_init(pthread_condattr_t *condattr) {
	if (!condattr) return __set_errno(-EINVAL);
	condattr->pshared = PTHREAD_PROCESS_PRIVATE;
	condattr->clock_id = CLOCK_MONOTONIC;
	return 0;
}
