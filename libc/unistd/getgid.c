#include <unistd.h>
#include <sysdeps.h>

gid_t getgid(void) {
	return sys_getgid();
}
