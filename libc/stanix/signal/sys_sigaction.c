#include <syscall.h>
#include <sysdeps.h>

int sys_sigaction(int signum, const struct sigaction *act, struct sigaction *oldact) {
	return __set_errno(__syscall3(SYS_sigaction, signum, (long)act, (long)oldact));
}
