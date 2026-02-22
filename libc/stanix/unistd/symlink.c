#include <unistd.h>
#include <errno.h>
#include <syscall.h>

int symlink(const char *target, const char *linkpath){
	return __set_errno(__syscall2(SYS_symlink,(long)target,(long)linkpath));
}