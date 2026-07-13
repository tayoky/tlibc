#include <unistd.h>
#include <sysdeps.h>

pid_t fork(void) {
	return CALL_SYSDEP(sys_fork, ());
}
