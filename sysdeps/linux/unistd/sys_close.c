#include <sysdeps.h>
#include <sys/syscall.h>
#include <unistd.h>

int sys_close(int fd) {
	return syscall(SYS_close, fd);
}
