#include <stdio.h>
#include <sysdeps.h>

int rename(const char *oldpath, const char *newpath) {
	return sys_rename(oldpath, newpath);
}
