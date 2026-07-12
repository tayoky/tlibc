#include <sys/stat.h>
#include <sysdeps.h>

int fstat(int fd, struct stat *buf) {
	return CALL_SYSDEP(sys_fstat, (fd, buf));
}
