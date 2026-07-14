#include <sysdeps.h>

TLIBC_WEAK gid_t sys_getgid(void) {
	// fake being root
	return 0;
}
