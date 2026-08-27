#include <sysdeps.h>
#include <syscall.h>

int chdir(const char *pathname) {
	return sys_chdir(pathname);
}
