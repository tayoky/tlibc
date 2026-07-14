#include <sysdeps.h>
#include <fcntl.h>

TLIBC_WEAK int sys_lstat(const char *pathname, struct stat *buf) {
#if defined(AT_FDCWD) && defined(AT_SYMLINK_NOFOLLOW)
	return sys_fstatat(AT_FDCWD, pathname, buf, AT_SYMLINK_NOFOLLOW);
#else
	// technically not correct
	// but most OSes without lstat don't support symlinks
	return sys_stat(pathname, buf);
#endif
}
