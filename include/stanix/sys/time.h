#ifndef SYS_TIME_H
#define SYS_TIME_H

#include <sys/type.h>

struct timeval {
	time_t      tv_sec;     /* seconds */
	suseconds_t tv_usec;    /* microseconds */
};

struct timezone {
	long stub;
};

int gettimeofday(struct timeval *tv,struct timezone *tz);

#endif