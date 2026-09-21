#ifndef _TIME_H
#define _TIME_H

#include <features.sh>
#include <sys/time.h>
#include <locale.h>

struct tm {
	int tm_sec;          // Seconds. [0-60] 1 leap second
	int tm_min;          // Minutes. [0-59]     
	int tm_hour;         // Hours.   [0-23]     
	int tm_mday;         // Day.     [1-31]     
	int tm_mon;          // Month.   [0-11]     
	int tm_year;         // Year - 1900.        
	int tm_wday;         // Day of week. [0-6]  
	int tm_yday;         // Days in year.[0-365]
	int tm_isdst;        // DST.     [-1/0/1]


#if defined(_DEFAULT_SOURCE) && _DEFAULT_SOURCE
	long int tm_gmtoff;  // Seconds east of UTC.  
	const char *tm_zone; // STimezone abbreviation.SS
#else
	unsigned long __padding0;
	char *__padding1;
#endif
};

time_t time(time_t * tloc);
double  difftime(time_t time1, time_t time0);
struct tm *gmtime(const time_t *clock);
struct tm *localtime(const time_t *clock);
char *asctime(const struct tm *timeptr);
char *ctime(const time_t *clock);
#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE
struct tm *gmtime_r(const time_t *clock, struct tm *tm);
struct tm *localtime_r(const time_t *clock, struct tm *tm);
char *asctime_r(const struct tm *timeptr, char *buf);
char *ctime_r(const time_t *clock, char *buf);
void tzset(void);
extern char *tzname[2];
#endif
time_t mktime(struct tm *);
clock_t clock(void);
#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 199309L
int clock_gettime(clockid_t clock_id, struct timespec *tp);
int clock_settime(clockid_t clock_id, const struct timespec *tp);
int nanosleep(const struct timespec *, struct timespec *);
#endif
size_t strftime(char *, size_t, const char *, const struct tm *);
size_t strftime_l(char *buf, size_t size, const char *fmt, const struct tm *tm,locale_t locale);


#if (defined(_XOPEN_SOURCE) && _XOPEN_SOURCE) || (defined(_DEFAULT_SOURCE) && _DEFAULT_SOURCE)
extern long timezone;
extern int daylight;
#endif

#define CLOCKS_PER_SEC 1000000

#endif
