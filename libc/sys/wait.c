#include <sys/wait.h>
#include <sysdeps.h>

pid_t wait(int *status) {
	// TODO : try wait4
	return waitpid(-1, status, 0);
}
