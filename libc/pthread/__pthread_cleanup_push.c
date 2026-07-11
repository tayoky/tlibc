#include <pthread.h>
#include <tlibc.h>

void __pthread_cleanup_push(struct __pthread_cleanup *cleanup, void (*routine)(void *), void *arg) {
	cleanup->next    = __get_uthread()->cleanups;
	cleanup->routine = routine;
	cleanup->arg     = arg;
	__get_uthread()->cleanups = cleanup;
}
