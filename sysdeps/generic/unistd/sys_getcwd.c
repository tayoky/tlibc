#include <sysdeps.h>

TLIBC_WEAK int sys_getcwd(char *buf, size_t size) {
	return SYSDEP_STUB;
}
