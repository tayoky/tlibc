#include <sysdeps.h>

TLIBC_WEAK int sys_setgid(gid_t gid) {
	return __set_errno(-ENOSYS);
}
