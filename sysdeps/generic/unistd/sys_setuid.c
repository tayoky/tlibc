#include <sysdeps.h>

TLIBC_WEAK int sys_setuid(uid_t uid) {
	return __set_errno(-ENOSYS);
}
