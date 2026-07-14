#include <sysdeps.h>

TLIBC_WEAK pid_t sys_gettid(void) {
	// probably a system without multithreading
	return sys_getpid();
}
