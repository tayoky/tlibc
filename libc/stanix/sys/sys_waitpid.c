#include <sysdeps.h>
#include <errno.h>
#include <syscall.h>

pid_t sys_waitpid(pid_t pid, int *status, int options) {
	return __set_errno(__syscall3(SYS_waitpid, (long)pid, (long)status, (long)options));
}
