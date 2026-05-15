#include <sys/module.h>
#include <errno.h>
#include <syscall.h>

int rmmod(const char *name) {
	return __set_errno(__syscall1(SYS_rmmod, (long)name));
}
