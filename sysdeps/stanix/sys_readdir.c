#include <sysdeps.h>
#include <syscall.h>
#include <errno.h>

int sys_readdir(int fd, struct dirent *entry, long index) {
	return __set_errno(__syscall3(SYS_readdir, fd, (long)entry, index));
}
