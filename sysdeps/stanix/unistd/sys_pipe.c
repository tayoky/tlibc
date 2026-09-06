#include <errno.h>
#include <syscall.h>
#include <sysdeps.h>

int sys_pipe(int pipefd[2]) {
	return __set_errno(__syscall1(SYS_pipe, (long)pipefd));
}
