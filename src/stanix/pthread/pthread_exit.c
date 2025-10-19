#include <pthread.h>
#include <syscall.h>
#include <tlibc.h>
#include <stdnoreturn.h>

noreturn void pthread_exit(void *retval){
	__free_uthread(__get_uthread());
	__syscall1(SYS_thread_exit,(long)retval);
	__builtin_unreachable();
}