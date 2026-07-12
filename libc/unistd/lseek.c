#include <unistd.h>
#include <sysdeps.h>

off_t lseek(int fd, off_t offset, int whence) {
	return CALL_SYSDEP(sys_lseek, (fd, offset, whence));
}
