#include <pthread.h>
#include <errno.h>

int pthread_condattr_getclock(const pthread_condattr_t *condattr, clockid_t *clock_id) {
	if (!condattr) return __set_errno(-EINVAL);
	*clock_id = condattr->clock_id;
	return 0;
}
