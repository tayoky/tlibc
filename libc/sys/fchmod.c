#include <sys/stat.h>
#include <sysdeps.h>

int fchmod(int fd, mode_t mode) {
	return CALL_SYSDEP(sys_fchmod, (fd, mode));
}
