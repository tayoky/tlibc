#include <sysdeps.h>
#include <signal.h>

int sigqueue(pid_t pid, int sig, const union sigval value) {
	return sys_sigqueue(pid, sig, value);
}
