#include <sysdeps.h>

TLIBC_WEAK int sys_getpriority(int which, id_t who) {
	(void)which;
	(void)who;
	return SYSDEP_STUB;
}
