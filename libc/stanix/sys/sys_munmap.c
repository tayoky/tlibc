#include <sysdeps.h>
#include <errno.h>
#include <syscall.h>

int sys_munmap(void *addr, size_t length) {
	return __set_errno(__syscall2(SYS_munmap, (long)addr, length));
}
