#include <sys/module.h>
#include <syscall.h>
#include <errno.h>

int insmod(const char *pathname,const char **argv){
	return __set_errno(__syscall2(SYS_insmod,(long)pathname,(long)argv));
}
