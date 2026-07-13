#include <unistd.h>
#include <sysdeps.h>

gid_t getgid(void) {
	if (sys_getgid) {
		return sys_getgid();
	} else {
		return 0;
	}
}
