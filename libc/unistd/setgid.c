#include <unistd.h>
#include <sysdeps.h>

int setgid(gid_t gid) {
	return sys_setgid(gid);
}
