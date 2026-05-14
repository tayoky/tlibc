#include <pthread.h>
#include <tlibc.h>
#include <limits.h>
#include <errno.h>

int pthread_setspecific(pthread_key_t key, const void *value) {
	if (key == 0 || key > PTHREAD_KEYS_MAX) return EINVAL;
	__get_uthread()->keys[key - 1] = (void*)value;
	return 0;
}
