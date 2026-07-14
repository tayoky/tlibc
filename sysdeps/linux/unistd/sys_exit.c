#include <sys/syscall.h>
#include <sysdeps.h>
#include <unistd.h>

int sys_exit(int status) {
	return syscall(SYS_exit_group, status);
}
