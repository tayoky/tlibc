#include <sysdeps.h>
#include <sys/syscall.h>
#include <unistd.h>

off_t sys_lseek(int fd, off_t offset, int whence) {
	return syscall(SYS_lseek, fd, offset, whence);
}
