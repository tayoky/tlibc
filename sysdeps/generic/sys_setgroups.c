#include <sysdeps.h>

TLIBC_WEAK int sys_setgroups(size_t size, const gid_t *list) {
	(void)size;
	(void)list;
	return SYSDEP_STUB;
}
