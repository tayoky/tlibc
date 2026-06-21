#include <errno.h>
#include <pthread.h>

int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict mutexattr) {
	if (!mutex) return __set_errno(-EINVAL);
	if (mutexattr) {
		mutex->attr = *mutexattr;
	} else {
		pthread_mutexattr_init(&mutex->attr);
	}
	mutex->lock = 0;
	mutex->lock_count = 0;
	return 0;
}
