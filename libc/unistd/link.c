#include <unistd.h>
#include <sysdeps.h>

int link(const char *oldpath, const char *newpath) {
	return CALL_SYSDEP(sys_link, (oldpath, newpath));
}
