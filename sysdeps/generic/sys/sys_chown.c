#include <sysdeps.h>

TLIBC_WEAK int sys_chown(const char *pathname, uid_t owner, gid_t group) {
	return __set_errno(-ENOSYS);
}
