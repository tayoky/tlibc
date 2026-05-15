#include <errno.h>
#include <sched.h>
#include <syscall.h>

pid_t gettid(void) {
	return __set_errno(__syscall0(SYS_gettid));
}
