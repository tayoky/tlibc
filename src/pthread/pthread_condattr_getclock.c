#include <pthread.h>
#include <errno.h>

int pthread_condattr_getclock(const pthread_condattr_t *restrict condattr, clockid_t *restrict clock_id) {
	if (!condattr) return __set_errno(-EINVAL);
	*clock_id = condattr->clock_id;
	return 0;
}
