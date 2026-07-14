#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <sysdeps.h>

int rmdir(const char *pathname) {
	return sys_rmdir(pathname);
}
