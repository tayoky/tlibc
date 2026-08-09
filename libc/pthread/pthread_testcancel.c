#include <pthread.h>
#include <tlibc.h>

void pthread_testcancel(void) {
	if (atomic_load(&__get_uthread()->cancel)) {
		pthread_exit(PTHREAD_CANCELED);
	}
}
