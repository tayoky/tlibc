#include <time.h>
#include <syscall.h>
#include <errno.h>


int nanosleep(const struct timespec *duration, struct timespec *rem){
	return __set_errno(__syscall2(SYS_nanosleep,(long)duration,(long)rem));
}
