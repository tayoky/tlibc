#include <errno.h>
#include <syscall.h>
#include <unistd.h>

int setuid(uid_t uid) {
	return __set_errno(__syscall1(SYS_setuid, uid));
}
