#include <unistd.h>
#include <syscall.h>
#include <errno.h>

int pipe(int pipefd[2]){
	return __set_errno(__syscall1(SYS_pipe,(long)pipefd));
}
