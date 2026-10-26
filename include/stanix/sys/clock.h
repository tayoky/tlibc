#ifndef _SYS_CLOCK_H
#define _SYS_CLOCK_H

#include <sys/types.h>
#include <sys/time.h>
#include <stdint.h>

typedef uint64_t clock_tick_t;

#define CLOCK_GET_INFO    19000
#define CLOCK_RECALIBRATE 19001
#define CLOCK_SELECT      19002
#define CLOCK_GET_TICK    19003
#define CLOCK_GET_TIME    19004

typedef struct clock_info {
	size_t frequency;
	size_t priority;
	struct timespec offset;
	size_t flags;
	size_t reserved[5];
} clock_info_t;

#define CLOCK_FLAG_STABLE_FREQ 0x01 // the frequence is always the same across different pieces of hardware

#endif
