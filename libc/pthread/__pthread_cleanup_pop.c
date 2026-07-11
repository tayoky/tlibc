#include <pthread.h>
#include <tlibc.h>

void __pthread_cleanup_pop(int execute) {
	struct __pthread_cleanup *cleanup = __get_uthread()->cleanups;
	if (!cleanup) return;
	__get_uthread()->cleanups = cleanup->next;

	if (execute) {
		if (cleanup->routine) {
			cleanup->routine(cleanup->arg);
		}
	}
}
