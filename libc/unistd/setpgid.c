#include <unistd.h>
#include <sysdeps.h>

int setpgid(pid_t pid, pid_t pgid) {
	return CALL_SYSDEP(sys_setpgid, (pid, pgid));
}
