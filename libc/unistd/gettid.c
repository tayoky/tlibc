#include <unistd.h>
#include <sysdeps.h>

pid_t gettid(void) {
	if (sys_gettid) {
		return sys_gettid();
	} else {
		// probably a system without multithreading
		return getpid();
	}
}
