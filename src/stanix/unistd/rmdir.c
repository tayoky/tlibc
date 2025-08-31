#include <unistd.h>
#include <syscall.h>
#include <errno.h>

int rmdir(const char *pathname){
	return __set_errno(__syscall1(SYS_rmdir,(long)pathname));
}
