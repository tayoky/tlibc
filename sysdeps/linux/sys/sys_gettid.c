#include <sysdeps.h>
#include <sys/syscall.h>
#include <unistd.h>

pid_t sys_gettid(void) {
	return syscall(SYS_gettid);
}
