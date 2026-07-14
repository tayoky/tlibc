#include <unistd.h>
#include <sysdeps.h>

pid_t getpid(void) {
	return sys_getpid();
}
