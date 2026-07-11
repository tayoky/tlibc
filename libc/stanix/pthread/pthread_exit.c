#include <pthread.h>
#include <syscall.h>
#include <tlibc.h>
#include <tlibcnoreturn.h>

TLIBC_NORETURN void pthread_exit(void *retval) {
	__get_uthread()->retval = retval;
	if (__get_uthread()->detach_state == PTHREAD_CREATE_DETACHED) {
		// TODO : free stack
		__free_uthread(__get_uthread());
	}
	__syscall0(SYS_thread_exit);
	__builtin_unreachable();
}
