#include <time.h>
#include <syscall.h>
#include <errno.h>

int clock_gettime(clockid_t clockid, struct timespec *tp){
	return __set_errno(__syscall2(SYS_clock_gettime,clockid,(long)tp));
}
