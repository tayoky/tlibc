#include <sysdeps.h>

TLIBC_WEAK int sys_lstat(const char *pathname, struct stat *st) {
	// technically not correct
	// but most OSes without lstat don't support symlinks
	return sys_stat(pathname, st);
}
