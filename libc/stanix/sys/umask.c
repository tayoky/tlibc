#include <sys/stat.h>
#include <syscall.h>
#include <errno.h>

mode_t umask(mode_t mask){
	return __set_errno(__syscall1(SYS_umask,mask));
}
