#include <time.h>
#include <stdio.h>
#include <locale.h>
#include <langinfo.h>
#include <stdlib.h>

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
		return snprintf(buf,size,"%d",tm->tm_sec);;
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
