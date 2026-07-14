#include <unistd.h>
#include <sysdeps.h>

uid_t geteuid(void) {
	return sys_geteuid();
}
