#include <sysdeps.h>

TLIBC_WEAK int sys_setuid(uid_t uid) {
	return SYSDEP_STUB;
}
