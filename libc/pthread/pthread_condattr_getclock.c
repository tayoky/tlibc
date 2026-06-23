#include <errno.h>
#include <pthread.h>

int pthread_condattr_getclock(const pthread_condattr_t *restrict condattr, clockid_t *restrict clock_id) {
	if (!condattr) return EINVAL;
	*clock_id = condattr->clock_id;
	return 0;
}
