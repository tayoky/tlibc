#include <sysdeps.h>

TLIBC_WEAK int sys_getgroups(int size, gid_t *list) {
	(void)size;
	(void)list;
	return SYSDEP_STUB;
}
