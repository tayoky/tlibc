#include <syscall.h>
#include <sysdeps.h>

int sys_sigprocmask(int how, const sigset_t *set, sigset_t *oldset) {
	return __set_errno(__syscall3(SYS_sigprogmask, how, (long)set, (long)oldset));
}
