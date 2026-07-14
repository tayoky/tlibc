#include <sysdeps.h>
#include <syscall.h>
#include <errno.h>

int sys_thread_exit(void) {
	return __set_errno(__syscall0(SYS_thread_exit));
}
