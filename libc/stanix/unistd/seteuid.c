#include <unistd.h>
#include <syscall.h>
#include <errno.h>

int seteuid(uid_t uid){
	return __set_errno(__syscall1(SYS_seteuid,uid));
}
