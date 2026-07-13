#include <unistd.h>
#include <sysdeps.h>

pid_t getpid(void) {
	if (sys_getpid) {
		return sys_getpid();
	} else {
		// fake a process ID
		return 1;
	}
}
