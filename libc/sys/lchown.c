#include <sys/stat.h>
#include <sysdeps.h>

int lchown(const char *pathname, uid_t owner, gid_t group) {
	if (sys_lchown) {
		return sys_lchown(pathname, owner, group);
	 } else if (sys_chown) {
		// technically not correct
		// but most OSes without lstat don't support symlinks
		return sys_chown(pathname, owner, group);
	 } else {
		return __set_errno(-ENOSYS);
	 }
}
