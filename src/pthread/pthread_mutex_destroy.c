#include <pthread.h>
#include <errno.h>

int pthread_mutex_destroy(pthread_mutex_t *mutex) {
	if (!mutex) return __set_errno(-EINVAL);
	pthread_mutexattr_destroy(&mutex->attr);
	return 0;
}
