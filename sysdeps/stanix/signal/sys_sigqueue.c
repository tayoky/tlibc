#include <syscall.h>
#include <sysdeps.h>

int sys_sigqueue(pid_t pid, int sig, const union sigval value) {
	return __set_errno(__syscall3(SYS_sigqueue, pid, sig, value.raw_data));
}
