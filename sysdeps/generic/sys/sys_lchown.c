#include <sysdeps.h>

TLIBC_WEAK int sys_lchown(const char *pathname, uid_t owner, gid_t group) {
	// technically not correct
	// but most OSes without lchown don't support symlinks
	return sys_chown(pathname, owner, group);
}
