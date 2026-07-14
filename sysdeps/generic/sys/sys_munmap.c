#include <sysdeps.h>

TLIBC_WEAK int sys_munmap(void *addr, size_t length) {
	return SYSDEP_STUB;
}
