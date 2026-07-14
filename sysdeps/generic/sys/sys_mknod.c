#include <sysdeps.h>

TLIBC_WEAK int sys_mknod(const char *pathname, mode_t mode, dev_t dev) {
	return SYSDEP_STUB;
}
