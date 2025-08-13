#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

char *tzname[2] = {NULL,NULL};
long timezone;
int daylight;

static int is_leap(long year){
	//not divisible by 4
	if(year % 4){
		return 0;
	}

	//exception for mutiple of 100 that can't be divided by 400
	if((year % 400) && !(year % 100)){
		return 0;
	}

	return 1;
}

static long nbofdayin(long year,int month){
	switch (month){
	case 12:
		return 31;
	case 11:
		return 30;
	case 10:
		return 31;
	case 9:
		return 30;
	case 8:
		return 31;
	case 7:
		return 31;
	case 6:
		return 30;
	case 5:
		return 31;
	case 4:
		return 30;
	case 3:
		return 31;
	case 2:
		if(is_leap(year)){
			return 29;
		} else {
			return 28;
		}
	case 1:
		return 31;
			
	default:
		return -1;
	}
}

clock_t    clock(void);
int        clock_getres(clockid_t, struct timespec *);
int        clock_settime(clockid_t, const struct timespec *);



struct tm *getdate(const char *);


struct tm *gmtime_r(const time_t *clock, struct tm *tm){
	if(!tm){
		return NULL;
	}

	tm->tm_gmtoff = 0;

	tm->tm_sec  = *clock % 60;
	tm->tm_min  = (*clock / 60) % 60;
	tm->tm_hour = (*clock / 3600) % 24;

	//day since 1 january 1970
	long day = (*clock / 86400);

	//the 1 january 1970 is an thursday
	tm->tm_wday = (day + 4) % 7;

	long year = 1970;
	for(;;){
		if(is_leap(year)){
			if(day < 366){
				break;
			}
			day -= 366;
		} else {
			if(day < 365){
				break;
			}
			day -= 365;
		}
		year++;
	}

	tm->tm_year = year - 1900;
	tm->tm_yday = day;
	
	int month = 1;
	for(;;){
		if(day < nbofdayin(year,month)){
			break;
		}
		day -= nbofdayin(year,month);
		month++;
	}

	tm->tm_mon = month - 1;
	tm->tm_mday = day + 1;

	return tm;
}


time_t mktime(struct tm *tm){
	time_t sec = tm->tm_hour * 3600 + tm->tm_min * 60 + tm->tm_sec;
	sec += tm->tm_yday * 86400;
	long year = tm->tm_year + 1900;
	while(year > 1970){
		year--;
		if(is_leap(year)){
			sec += 366 * 86400;
		} else {
			sec += 365 * 86400;
		}
	}
	return sec;
}
int        nanosleep(const struct timespec *, struct timespec *);



char      *strptime(const char *, const char *, struct tm *);

int clock_gettime(clockid_t clock_id, struct timespec *tp){
	struct timeval tv;
	switch(clock_id){
	case CLOCK_REALTIME:
	case CLOCK_MONOTONIC:
		gettimeofday(&tv,NULL);
		tp->tv_sec = tv.tv_sec; 
		tp->tv_nsec = tv.tv_usec * 1000; 
		return 0;
	default:
		return -EINVAL;
	}
}

time_t time(time_t * tloc){
	struct timeval tv;
	if(gettimeofday(&tv,NULL)){
		if(tloc){
			*tloc = 0;
		}
		return 0;
	}
	if(tloc){
		*tloc = tv.tv_sec;
	}
	return tv.tv_sec;
}
