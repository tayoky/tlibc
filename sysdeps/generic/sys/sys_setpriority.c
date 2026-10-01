#include <sysdeps.h>

TLIBC_WEAK int sys_setpriority(int which, id_t who, int value) {
	(void)which;
	(void)who;
	(void)value;
	return SYSDEP_STUB;
}
