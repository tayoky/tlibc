#include <unistd.h>
#include <sysdeps.h>

int setegid(gid_t gid) {
	return CALL_SYSDEP(sys_setegid, (gid));
}
