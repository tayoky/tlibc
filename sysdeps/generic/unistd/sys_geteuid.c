#include <sysdeps.h>

TLIBC_WEAK uid_t sys_geteuid(void) {
	// fake being root
	return 0;
}
