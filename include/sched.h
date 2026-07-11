#ifndef _SCHED_H
#define _SCHED_H

#include <abi/sched.h>
#include <sys/types.h>

int sched_get_priority_max(int policy);
int sched_get_priority_min(int policy);
int sched_yield(void);

#endif
