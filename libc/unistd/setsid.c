#include <sysdeps.h>
#include <unistd.h>

pid_t setsid(void) {
	return sys_setsid();
}
