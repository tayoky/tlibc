#include <unistd.h>
#include <sysdeps.h>

uid_t getuid(void) {
	return sys_getuid();
}
