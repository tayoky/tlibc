#ifndef TIME_H
#define TIME_H

#include <sys/time.h>

struct tm {
	int tm_sec;          //Seconds. [0-60] 1 leap second
	int tm_min;          //Minutes. [0-59]     
	int tm_hour;         //Hours.   [0-23]     
	int tm_mday;         //Day.     [1-31]     
	int tm_mon;          //Month.   [0-11]     
	int tm_year;         //Year - 1900.        
	int tm_wday;         //Day of week. [0-6]  
	int tm_yday;         //Days in year.[0-365]
	int tm_isdst;        //DST.     [-1/0/1]

	long int tm_gmtoff;  //Seconds east of UTC.  
	const char *tm_zone; //STimezone abbreviation.SS
};


typedef long clock_t;
typedef int clockid_t;

time_t time(time_t * tloc);
struct tm *gmtime(const time_t *clock);
struct tm *gmtime_r(const time_t *clock, struct tm *tm);
struct tm *localtime(const time_t *clock);
struct tm *localtime_r(const time_t *clock, struct tm *tm);
char *asctime(const struct tm *timeptr);
char *asctime_r(const struct tm *timeptr, char *buf);
char *ctime(const time_t *clock);
char *ctime_r(const time_t *clock, char *buf);

#endif