#include <pthread.h>
#include <tlibc.h>
#include <limits.h>
#include <errno.h>

void *pthread_getspecific(pthread_key_t key) {
	if (key == 0 || key > PTHREAD_KEYS_MAX) return NULL;
	return __get_uthread()->keys[key - 1];
}
