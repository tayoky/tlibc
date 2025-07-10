#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include <langinfo.h>

char *tzname[2] = {NULL,NULL};
long timezone;
int daylight;

static struct tm default_tm;
static char default_buf[26];

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

char *asctime(const struct tm *timeptr){
	return asctime_r(timeptr,default_buf);
}

char *asctime_r(const struct tm *timeptr, char *buf){
    static const char *wday_name[] = {
        "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
    };
    static const char *mon_name[] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    sprintf(buf,"%s %s %2d %02d:%02d:%02d %d\n",
        wday_name[timeptr->tm_wday],
        mon_name[timeptr->tm_mon],
        timeptr->tm_mday, timeptr->tm_hour,
        timeptr->tm_min, timeptr->tm_sec,
        1900 + timeptr->tm_year);
    return buf;
}

clock_t    clock(void);
int        clock_getres(clockid_t, struct timespec *);
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

struct tm *localtime(const time_t *clock){
	tzset();
	return localtime_r(clock,&default_tm);
}

struct tm *localtime_r(const time_t *clock, struct tm *tm){
	time_t local_clock = *clock - timezone;
	return gmtime_r(&local_clock,tm);
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

static size_t strftimef(const char **fmt,char *buf,size_t size,const struct tm *tm,locale_t locale){
	switch(**fmt){
	case '%':
		*buf = '%';
		return 1;
	case 'a':
		return snprintf(buf,size,"%s",nl_langinfo_l(ABDAY_1 + tm->tm_wday,locale));
	case 'A':
		return snprintf(buf,size,"%s",nl_langinfo_l(DAY_1 + tm->tm_wday,locale));
	case 'h':
	case 'b':
		return snprintf(buf,size,"%s",nl_langinfo_l(ABMON_1 + tm->tm_mon,locale));
	case 'B':
		return snprintf(buf,size,"%s",nl_langinfo_l(MON_1 + tm->tm_mon,locale));
	case 'c':
		return strftime_l(buf,size,nl_langinfo_l(D_T_FMT,locale),tm,locale);
	case 'C':
		return snprintf(buf,size,"%2d",(tm->tm_year + 1900)/100);
	case 'd':
		return snprintf(buf,size,"%d",tm->tm_mday);
	case 'D':
		return strftime_l(buf,size,"%m/%d/%y",tm,locale);
	case 'e':
		return snprintf(buf,size,"% 2d",tm->tm_mday);
	case 'g':
		return snprintf(buf,size,"%2d",(tm->tm_year + 1900)%100);
	case 'G':
		return snprintf(buf,size,"%d",(tm->tm_year + 1900));
	case 'H':
		return snprintf(buf,size,"%d",tm->tm_hour);
	case 'I':
		return snprintf(buf,size,"%d",((tm->tm_hour + 11)%12)+1);
	case 'j':
		return snprintf(buf,size,"%d",tm->tm_yday);
	case 'm':
		return snprintf(buf,size,"%d",tm->tm_mon);
	case 'M':
		return snprintf(buf,size,"%d",tm->tm_min);
	case 'n':
		*buf = '\n';
		return 1;
	case 'p':
		return snprintf(buf,size,"%s",nl_langinfo_l(tm->tm_hour > 12 || tm->tm_hour == 0 ? PM_STR : AM_STR,locale));
	case 'r':
		return strftime_l(buf,size,nl_langinfo_l(T_FMT_AMPM,locale),tm,locale);
	case 'R':
		return snprintf(buf,size,"%d:%d",tm->tm_hour,tm->tm_min);
	case 'S':
		return snprintf(buf,size,"%d",tm->tm_sec);
	case 't':
		*buf = '\t';
		return 1;
	case 'T':
		return snprintf(buf,size,"%d:%d:%d",tm->tm_hour,tm->tm_min,tm->tm_sec);
	case 'u':
		return snprintf(buf,size,"%d",tm->tm_wday == 0 ? 7 : tm->tm_wday);
	case 'w':
		return snprintf(buf,size,"%d",tm->tm_wday);
	case 'x':
		return strftime_l(buf,size,nl_langinfo_l(D_FMT,locale),tm,locale);
	case 'X':
		return strftime_l(buf,size,nl_langinfo_l(T_FMT,locale),tm,locale);
	case 'y':
		return snprintf(buf,size,"%d",(tm->tm_year + 1900)% 100);
	case 'Y':
		return snprintf(buf,size,"%d",tm->tm_year + 1900);
	case 'z':
		return snprintf(buf,size,"%c%02d%02d",timezone > 0 ? '-' : '+',abs(timezone)/60,abs(timezone)%60);
	case 'Z':
		return snprintf(buf,size,"%s",tzname[0]);
	default:
		return 0;
	}
}

size_t strftime(char *buf, size_t size, const char *fmt, const struct tm *tm){
	return strftime_l(buf,size,fmt,tm,uselocale((locale_t)0));
}

size_t strftime_l(char *buf, size_t size, const char *fmt, const struct tm *tm,locale_t locale){
	tzset();
	size_t len = 0;
	while(*fmt){
		if(!size)break;
		switch(*fmt){
		case '%':
			fmt++;
			size_t l = strftimef(&fmt,buf,size,tm,locale);
			size -= l;
			len += l;
			buf += l;
			break;
		default:
			*buf = *fmt;
			buf++;
			len++;
			size--;
			break;
		}
		fmt++;
	}
	if(size > 0){
		*buf = '\0';
	}
	return len;
}

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

static char *get_str(char *tz,char **end){
	char *start = tz;
	int extended = 0;
	for(;;){
		switch(*tz){
		case '\0':
			return NULL;
		case '<':
			extended = 1;
			tz++;
			continue;
		case '>':
			extended = 0;
			tz++;
			continue;
		case '-':
		case '+':
			if(!extended)goto finish;
		}
		if(isdigit(*tz)){
			if(!extended)goto finish;
		}
		if(!isalpha(*tz)){
			return NULL;
		}

		tz++;
	}
finish:
	if(tz - start < 3)return NULL;
	*end = tz;
	return strndup(start,tz - start);
}

static long get_offset(char *tz,char **end,int *error){
	int sign = 1;
	switch(*tz){
	case '+':
		tz++;
		break;
	case '-':
		sign = -1;
		tz++;
		break;
	}

	long off = 0;
	char *e;

	for(long mul=3600; mul>=1; mul/=60){
		off += strtol(tz,&e,10) * mul;
		if(e == tz){
			*error = 1;
			return 0;
		}
		tz = e;
		if(*tz != ':'){
			*end = tz;
			return sign * off;
		}
	}
	*end = tz;
	return sign * off;
}
//TODO : parse timezone file
void tzset(void){
	char *tz = getenv("TZ");
	if(!tz){
fallback:
		free(tzname[0]);
		free(tzname[1]);
		tzname[0] = strdup("UTC");
		tzname[1] = strdup("UTC");
		timezone = 0;
		daylight = 0;
		return;
	}
	int error = 0;

	if(*tz == ',')tz++;
	char *std = get_str(tz,&tz);
	if(!std)goto fallback;
	long off = get_offset(tz,&tz,&error);
	if(error){
		free(std);
		goto fallback;
	}

	free(tzname[0]);
	free(tzname[1]);

	tzname[0] = std;
	tzname[1] = strdup(std);
	timezone = off;
	daylight = 0;
}
