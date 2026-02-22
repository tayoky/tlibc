#include <time.h>
#include <syscall.h>
#include <errno.h>

int clock_settime(clockid_t clockid, struct timespec *tp){
	return __set_errno(__syscall2(SYS_clock_settime,clockid,(long)tp));
}
