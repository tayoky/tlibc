#include <signal.h>
#include <sysdeps.h>

int sigpending(sigset_t *set) {
	return sys_sigpending(set);
}
