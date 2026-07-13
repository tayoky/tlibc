#include <unistd.h>
#include <sysdeps.h>

gid_t getegid(void) {
	if (sys_getegid) {
		return sys_getegid();
	} else {
		return 0;
	}
}
