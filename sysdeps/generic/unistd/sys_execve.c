#include <sysdeps.h>

TLIBC_WEAK int sys_execve(const char *pathname, char *const *argv, char *const *envp) {
	return SYSDEP_STUB;
}
