#include <signal.h>
#include <unistd.h>
#include <sysdeps.h>

int kill(pid_t pid, int sig) {
	return sys_kill(pid, sig);
}
