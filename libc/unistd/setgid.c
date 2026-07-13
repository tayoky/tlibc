#include <unistd.h>
#include <sysdeps.h>

int setgid(gid_t gid) {
	return CALL_SYSDEP(sys_setgid, (gid));
}
