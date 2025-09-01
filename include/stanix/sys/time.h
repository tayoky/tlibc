#ifndef SYS_TIME_H
#define SYS_TIME_H

#include <sys/type.h>

struct timeval {
	time_t      tv_sec;  //seconds
	suseconds_t tv_usec; //microseconds
};

struct timespec {
	time_t tv_sec; //seconds
	long tv_nsec;  //nanoseconds
};

struct timezone {
	int tz_minuteswest;
	int tz_dsttime;
};

int gettimeofday(struct timeval *tv, struct timezone *tz);

#endif
