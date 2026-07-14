#include <unistd.h>
#include <sysdeps.h>

gid_t getegid(void) {
	return sys_getegid();
}
