#ifndef _SYS_TIME_H
#define _SYS_TIME_H

#include <features.h>
#include <abi/time.h>
#include <sys/types.h>

#if defined(_DEFAULT_SOURCE) && _DEFAULT_SOURCE
int gettimeofday(struct timeval *tv, struct timezone *tz);
#endif
int utimes(const char *filename, const struct timeval times[2]);

#endif
