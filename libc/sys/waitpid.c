#include <sys/wait.h>
#include <sysdeps.h>

pid_t waitpid(pid_t pid, int *status, int options) {
	return sys_waitpid(pid, status, options);
}
