#include <syscall.h>
#include <sysdeps.h>

void sys_sync(void) {
	__syscall0(SYS_sync);
}
