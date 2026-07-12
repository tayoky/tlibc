#include <unistd.h>
#include <sysdeps.h>

int unlink(const char *pathname) {
	return CALL_SYSDEP(sys_unlink, (pathname));
}
