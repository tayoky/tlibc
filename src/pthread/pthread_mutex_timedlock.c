#include <pthread.h>
#include <errno.h>

int pthread_mutex_timedlock(pthread_mutex_t *restrict mutex, const struct timespec *restrict timeout) {
	if (!mutex) return __set_errno(-EINVAL);
	// TODO
	return __set_errno(-ENOSYS);
}
