#include <errno.h>
#include <pthread.h>

int pthread_condattr_setclock(pthread_condattr_t *condattr, clockid_t clock_id) {
	if (!condattr) return EINVAL;
	condattr->clock_id = clock_id;
	return 0;
}
