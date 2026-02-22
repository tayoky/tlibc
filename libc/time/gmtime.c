#include <time.h>

struct tm *gmtime(const time_t *clock){
	static struct tm tm;
	return gmtime_r(clock,&tm);
}
