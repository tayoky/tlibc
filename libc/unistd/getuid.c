#include <unistd.h>
#include <sysdeps.h>

uid_t getuid(void) {
	if (sys_getuid) {
		return sys_getuid();
	} else {
		return 0;
	}
}
