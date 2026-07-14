#include <sysdeps.h>

TLIBC_WEAK int sys_setegid(gid_t gid) {
	return __set_errno(-ENOSYS);
}
