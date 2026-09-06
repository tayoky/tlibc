#include <sysdeps.h>
#include <unistd.h>

int pipe(int pipefd[2]) {
	return sys_pipe(pipefd);
}
