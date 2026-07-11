#ifndef _SYS_TIME_H
#define _SYS_TIME_H

#include <abi/time.h>
#include <sys/types.h>

int gettimeofday(struct timeval *tv, struct timezone *tz);
int utimes(const char *filename, const struct timeval times[2]);

#endif
