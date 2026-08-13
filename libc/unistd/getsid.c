#include <sysdeps.h>
#include <unistd.h>

pid_t getsid(void) {
	return sys_getsid();
}
