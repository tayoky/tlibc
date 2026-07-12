#ifndef _ABI_SCHED_H
#define _ABI_SCHED_H

// Stub sched ABI

#include <sys/types.h>

struct sched_param {
	int sched_priority;
};

#define SCHED_OTHER 0
#define SCHED_RR    1
#define SCHED_FIFO  2

#endif
