#include <pthread.h>
#include <errno.h>

int pthread_condattr_setclock(pthread_condattr_t *condattr, clockid_t clock_id) {
	if (!condattr) return __set_errno(-EINVAL);
	condattr->clock_id = clock_id;
	return 0;
}
