#include <time.h>

//FIXME : tzset ?

struct tm *localtime_r(const time_t *clock, struct tm *tm){
	time_t local_clock = *clock - timezone;
	return gmtime_r(&local_clock,tm);
}
