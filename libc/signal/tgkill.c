#include <sysdeps.h>
#include <signal.h>

int tgkill(pid_t pid, pid_t tid, int sig) {
	return sys_tgkill(pid, tid, sig);
}
