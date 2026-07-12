#include <errno.h>
#include <syscall.h>
#include <unistd.h>

int dup2(int oldfd, int newfd) {
	return __set_errno(__syscall2(SYS_dup2, (long)oldfd, (long)newfd));
}
