#include <pthread.h>
#include <errno.h>

int pthread_rwlock_destroy(pthread_rwlock_t *rwlock) {
	if (!rwlock) return EINVAL;
	return 0;
}
