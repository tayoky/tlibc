#include <unistd.h>
#include <syscall.h>
#include <errno.h>

int chdir(const char *path){
	return __set_errno(__syscall1(SYS_chdir,(long)path));
}
