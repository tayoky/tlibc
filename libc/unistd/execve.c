#include <unistd.h>
#include <sysdeps.h>

int execve(const char *pathname, char *const *argv, char *const *envp) {
	return CALL_SYSDEP(sys_execve, (pathname, argv, envp));
}
