#include <sysdeps.h>

TLIBC_WEAK int sys_mprotect(void *addr, size_t size, int prot) {
	return SYSDEP_STUB;
}
