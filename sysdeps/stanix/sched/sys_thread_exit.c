#include <sysdeps.h>
#include <syscall.h>
#include <errno.h>

TLIBC_NORETURN void sys_thread_exit(void) {
	__set_errno(__syscall0(SYS_thread_exit));
	__builtin_unreachable();
}
