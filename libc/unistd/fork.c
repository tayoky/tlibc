#include <unistd.h>
#include <sysdeps.h>

pid_t fork(void) {
	return sys_fork();
}
