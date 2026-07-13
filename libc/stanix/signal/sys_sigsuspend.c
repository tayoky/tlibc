#include <syscall.h>
#include <sysdeps.h>

int sys_sigsuspend(const sigset_t *mask) {
	return __set_errno(__syscall1(SYS_sigsuspend, (long)mask));
}
