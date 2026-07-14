#include <sysdeps.h>

TLIBC_WEAK int sys_lchmod(const char *pathname, mode_t mode) {
	// technically not correct
	// but most OSes without lchmod don't support symlinks
	return sys_chmod(pathname, mode);
}
