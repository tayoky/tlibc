#include <errno.h>
#include <syscall.h>
#include <sysdeps.h>

int sys_getcwd(char *buf, size_t size) {
	return __set_errno(__syscall2(SYS_getcwd, (long)buf, (long)size));
}
