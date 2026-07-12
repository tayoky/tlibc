#include <errno.h>
#include <syscall.h>
#include <unistd.h>

pid_t fork(void) {
	return __set_errno(__syscall0(SYS_fork));
}
