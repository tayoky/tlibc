#include <time.h>

struct tm *localtime(const time_t *clock){
	tzset();
	static struct tm tm;
	return localtime_r(clock,&tm);
}
