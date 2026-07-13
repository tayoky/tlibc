#include <unistd.h>
#include <sysdeps.h>

uid_t geteuid(void) {
	if (sys_geteuid) {
		return sys_geteuid();
	} else {
		return 0;
	}
}
