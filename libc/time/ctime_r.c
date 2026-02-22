#include <time.h>

char *ctime_r(const time_t *clock, char *buf){
	struct tm tm;
	return asctime_r(localtime_r(clock,&tm),buf);
}
