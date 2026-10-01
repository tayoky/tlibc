#include <sysdeps.h>

TLIBC_WEAK int sys_setrlimit(int resource, const struct rlimit *rlp) {
	(void)resource;
	(void)rlp;
	return SYSDEP_STUB;
}
