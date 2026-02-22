#include <sched.h>
#include <syscall.h>
#include <errno.h>

int stanix_join_thread(pid_t tid, void **arg){
	return __set_errno(__syscall2(SYS_join_thread, tid, (long)arg));
}