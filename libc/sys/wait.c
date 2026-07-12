#include <sys/wait.h>
#include <sysdeps.h>

pid_t wait(int *status) {
	if (sys_waitpid) {
		return waitpid(-1, status, 0);
	} else {
		// TODO : try wait4
		return __set_errno(-ENOSYS);
	}
}
