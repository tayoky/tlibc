#include <sys/stat.h>
#include <sysdeps.h>

int lchmod(const char *pathname, mode_t mode) {
	if (sys_lchmod) {
		return sys_lchmod(pathname, mode);
	} else if (sys_chmod) {
		// technically not correct
		// but most OSes without lstat don't support symlinks
		return sys_chmod(pathname, mode);
	} else {
		return __set_errno(-ENOSYS);
	}
}
