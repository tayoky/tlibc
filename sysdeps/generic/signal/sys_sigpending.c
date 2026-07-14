#include <sysdeps.h>

TLIBC_WEAK int sys_sigpending(sigset_t *set) {
	return SYSDEP_STUB;
}
