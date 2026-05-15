#include <errno.h>
#include <syscall.h>
#include <unistd.h>

int execve(const char *pathname, char *const *argv, char *const *envp) {
	return __set_errno(__syscall3(SYS_execve, (long)pathname, (long)argv, (long)envp));
}
