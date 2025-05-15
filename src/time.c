#include <time.h>
#include <unistd.h>
#include <stdio.h>

static struct tm default_tm;
static char default_buf[26];

static int is_leap(long year){
	//not divisible by 4
	if(year % 4){
		return 0;
	}

	//excecptioh for mutiple of 100 tha can't be divide by 400
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

char *asctime(const struct tm *timeptr){
	return asctime_r(timeptr,default_buf);
}

char *asctime_r(const struct tm *timeptr, char *buf){
    static char wday_name[7][3] = {
        "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
    };
    static char mon_name[12][3] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    static char result[26];

    sprintf(buf,"%s %s %2d %2d:%2d:%2d %d\n",
        wday_name[timeptr->tm_wday],
        mon_name[timeptr->tm_mon],
        timeptr->tm_mday, timeptr->tm_hour,
        timeptr->tm_min, timeptr->tm_sec,
        1900 + timeptr->tm_year);
    return result;
}

clock_t    clock(void);
int        clock_getres(clockid_t, struct timespec *);
int        clock_gettime(clockid_t, struct timespec *);
int        clock_settime(clockid_t, const struct timespec *);

char *ctime(const time_t *clock){
	return asctime(localtime(clock));
}

char *ctime_r(const time_t *clock, char *buf){
	struct tm tm;
	return asctime_r(localtime_r(clock,&tm),buf);
}

double  difftime(time_t time1, time_t time0){
	return (double)(time1 - time0);
}

struct tm *getdate(const char *);

struct tm *gmtime(const time_t *clock){
	return gmtime_r(clock,&default_tm);
}

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

	tm->tm_year = year - 1970;
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
	tm->tm_mday = day;

	return tm;
}

struct tm *localtime(const time_t *clock){
	return localtime_r(clock,&default_tm);
}

struct tm *localtime_r(const time_t *clock, struct tm *tm){
	return gmtime_r(clock,tm);
}

time_t     mktime(struct tm *);
int        nanosleep(const struct timespec *, struct timespec *);
size_t     strftime(char *, size_t, const char *, const struct tm *);
char      *strptime(const char *, const char *, struct tm *);

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

void       tzset(void);