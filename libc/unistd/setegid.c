#include <unistd.h>
#include <sysdeps.h>

int setegid(gid_t gid) {
	return sys_setegid(gid);
}
