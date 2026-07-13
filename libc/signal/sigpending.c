#include <signal.h>
#include <sysdeps.h>

int sigpending(sigset_t *set) {
	return CALL_SYSDEP(sys_sigpending, (set));
}
