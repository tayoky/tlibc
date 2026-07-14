#include <unistd.h>
#include <sysdeps.h>

pid_t gettid(void) {
	return sys_gettid();
}
