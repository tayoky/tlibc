#include <sysdeps.h>

TLIBC_WEAK int sys_fchown(int fd, uid_t owner, gid_t group) {
	return __set_errno(-ENOSYS);
}
