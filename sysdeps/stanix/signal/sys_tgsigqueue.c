#include <syscall.h>
#include <sysdeps.h>

int sys_tgsigqueue(pid_t pid, pid_t tid, int sig, const union sigval value) {
	return __set_errno(__syscall4(SYS_tgsigqueue, pid, tid, sig, value.raw_data));
}
