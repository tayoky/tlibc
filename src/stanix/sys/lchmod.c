#include <sys/stat.h>
#include <syscall.h>
#include <errno.h>

int lchmod(const char *pathname,mode_t mode){
	return __set_errno(__syscall2(SYS_lchmod,(long)pathname,mode));
}
