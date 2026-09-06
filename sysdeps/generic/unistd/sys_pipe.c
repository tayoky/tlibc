#include <sysdeps.h>

int sys_pipe(int pipefd[2]) {
	(void)pipefd;
	return SYSDEP_STUB;
}
