#include <sysdeps.h>

TLIBC_WEAK int sys_readdir(int fd, struct dirent *entry, long index) {
	return __set_errno(-ENOSYS);
}
