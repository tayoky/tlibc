#include <signal.h>
#include <sysdeps.h>

sighandler_t signal(int signum, sighandler_t handler) {
	return sys_signal(signum, handler);
}
