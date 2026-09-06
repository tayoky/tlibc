#include <sysdeps.h>

TLIBC_WEAK int sys_pipe(int pipefd[2]) {
	(void)pipefd;
	return SYSDEP_STUB;
}
