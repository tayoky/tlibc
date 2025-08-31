#include <unistd.h>
#include <syscall.h>
#include <errno.h>
#include <sys/time.h>

//FIXME: this should be implemented using clock_gettime when kernel get proper api
int gettimeofday(struct timeval *tv,struct timezone *tz){
	return __set_errno(__syscall2(SYS_gettimeofday,(long)tv,(long)tz));
}
