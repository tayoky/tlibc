#include <errno.h>
#include <syscall.h>
#include <unistd.h>

int dup(int oldfd) {
	return __set_errno(__syscall1(SYS_dup, (long)oldfd));
}
