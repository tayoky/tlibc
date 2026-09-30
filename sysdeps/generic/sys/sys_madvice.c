#include <sysdeps.h>

TLIBC_WEAK int sys_madvise(void *addr, size_t size, int advice) {
	(void)addr;
	(void)size;
	(void)advice;

	// madvise is only for performance
	// not returning an error is fine
	SYSDEP_STUB;
	return 0;
}
