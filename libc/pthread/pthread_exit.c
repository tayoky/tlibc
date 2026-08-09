#include <pthread.h>
#include <sysdeps.h>
#include <tlibc.h>
#include <tlibcnoreturn.h>

TLIBC_NORETURN void pthread_exit(void *retval) {
	// run cleanups
	for (struct __pthread_cleanup *cleanup = __get_uthread()->cleanups; cleanup; cleanup = cleanup->next) {
		if (cleanup->routine) {
			cleanup->routine(cleanup->arg);
		}
	}
	__get_uthread()->retval = retval;
	if (atomic_load(&__get_uthread()->detach_state) == PTHREAD_CREATE_DETACHED) {
		// TODO : free stack
		__free_uthread(__get_uthread());
	} else {
		atomic_store(&__get_uthread()->futex, 1);
		sys_futex_wait(&__get_uthread()->futex, INT_MAX);
	}
	sys_thread_exit();
}
