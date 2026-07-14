#include <sysdeps.h>

TLIBC_WEAK pid_t sys_getpid(void) {
	// fake a process ID
	return 1;
}
