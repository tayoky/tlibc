#include <pthread.h>
#include <tlibc.h>

void pthread_testcancel(void) {
	if (__get_uthread()->cancel) {
		pthread_exit(PTHREAD_CANCELED);
	}
}
