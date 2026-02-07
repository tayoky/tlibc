#include <pthread.h>
#include <errno.h>

int pthread_mutex_unlock(pthread_mutex_t *mutex) {
	if (!mutex) return __set_errno(-EINVAL);
	// TODO
	return __set_errno(-ENOSYS);
}
