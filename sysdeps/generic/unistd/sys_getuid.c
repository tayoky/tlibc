#include <sysdeps.h>

TLIBC_WEAK uid_t sys_getuid(void) {
	// fake being root
	return 0;
}
