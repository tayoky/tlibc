#include <syscall.h>
#include <sysdeps.h>

void sys_sync(void) {
	return __set_errno(__syscall0(SYS_sync));
}
