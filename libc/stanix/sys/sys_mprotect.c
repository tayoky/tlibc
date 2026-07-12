#include <sysdeps.h>
#include <errno.h>
#include <syscall.h>

int sys_mprotect(void *addr, size_t size, int prot) {
	return __set_errno(__syscall3(SYS_mprotect, (long)addr, size, prot));
}
