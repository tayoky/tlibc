#include <unistd.h>
#include <syscall.h>
#include <errno.h>

int unlink(const char *pathname){
	return __set_errno(__syscall1(SYS_unlink,(long)pathname));
}
