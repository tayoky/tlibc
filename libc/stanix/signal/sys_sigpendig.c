#include <syscall.h>
#include <sysdeps.h>

int sys_sigpending(sigset_t *set) {
	return __set_errno(__syscall1(SYS_sigpending, (long)set));
}
