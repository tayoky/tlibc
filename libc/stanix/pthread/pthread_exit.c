#include <pthread.h>
#include <syscall.h>
#include <tlibc.h>
#include <tlibcnoreturn.h>

TLIBC_NORETURN void pthread_exit(void *retval) {
	if (__get_uthread()->detach_state == PTHREAD_CREATE_DETACHED) {
		// TODO : free stack
		__free_uthread(__get_uthread());
	}
	__syscall1(SYS_thread_exit, (long)retval);
	__builtin_unreachable();
}
