#include <unistd.h>
#include <syscall.h>
#include <errno.h>

gid_t getegid(void){
	return __set_errno(__syscall0(SYS_getegid));
}
