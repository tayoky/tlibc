#ifndef _ABI_TIME_H
#define _ABI_TIME_H

// Stanix time ABI

#include <sys/types.h>

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

typedef long clock_t;
typedef int clockid_t;

#define CLOCK_REALTIME  0
#define CLOCK_MONOTONIC 1

#endif
