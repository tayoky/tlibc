#include <pthread.h>
#include <sys/mman.h>
#include <tlibc.h>
#include <errno.h>
#include <sysdeps.h>

int pthread_join(pthread_t thread, void **arg) {
	if (thread->detach_state != PTHREAD_CREATE_JOINABLE) {
		return EINVAL;
	}
	// some OSes need a join
	int ret = sys_join_thread(thread->tid, NULL);
	if (ret < 0 && errno != ENOSYS	) return errno;
	
	// TODO : use a futex if no join
	if (arg) *arg = thread->retval;
	if (thread->stack_is_allocated) {
		munmap(thread->stack, thread->stack_size);
	}
	__free_uthread(thread);
	return 0;
}
