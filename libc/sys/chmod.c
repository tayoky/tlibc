#include <sys/stat.h>
#include <sysdeps.h>

int chmod(const char *pathname, mode_t mode) {
	return CALL_SYSDEP(sys_chmod, (pathname, mode));
}
