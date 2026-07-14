#include <sysdeps.h>

TLIBC_WEAK int sys_seteuid(uid_t uid) {
	return SYSDEP_STUB;
}
