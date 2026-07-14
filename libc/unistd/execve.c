#include <unistd.h>
#include <sysdeps.h>

int execve(const char *pathname, char *const *argv, char *const *envp) {
	return sys_execve(pathname, argv, envp);
}
