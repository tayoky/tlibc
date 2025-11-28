#include <time.h>
#include <langinfo.h>
#include <stdio.h>

char *asctime_r(const struct tm *timeptr, char *buf){
    sprintf(buf,"%s %s %2d %02d:%02d:%02d %d\n",
        nl_langinfo(ABDAY_1 + timeptr->tm_wday),
        nl_langinfo(ABMON_1 + timeptr->tm_mon),
        timeptr->tm_mday, timeptr->tm_hour,
        timeptr->tm_min, timeptr->tm_sec,
        1900 + timeptr->tm_year);
    return buf;
}
