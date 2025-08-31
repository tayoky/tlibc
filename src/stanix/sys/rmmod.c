#include <sys/module.h>
#include <syscall.h>
#include <errno.h>

int rmmod(const char *name){
	return __set_errno(__syscall1(SYS_rmmod,(long)name));
}
