#include <unistd.h>
#include <sysdeps.h>

pid_t getpgid(pid_t pid) {
	return CALL_SYSDEP(sys_getpgid, (pid));
}
