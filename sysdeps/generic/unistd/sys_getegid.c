#include <sysdeps.h>

TLIBC_WEAK gid_t sys_getegid(void) {
	// fake being root
	return 0;
}
