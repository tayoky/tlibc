#include <unistd.h>
#include <syscall.h>
#include <errno.h>

int dup(int oldfd){
	return __set_errno(__syscall1(SYS_dup,(long)oldfd));
}
