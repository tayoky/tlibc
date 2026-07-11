#ifndef _ABI_SCHED_H
#define _ABI_SCHED_H

// Stanix sched ABI

#include <sys/types.h>

struct sched_param {
	int sched_priority;
};

#define SCHED_OTHER 0
#define SCHED_RR    1
#define SCHED_FIFO  2

#ifdef __TLIBC__
int sys_new_thread(void (*fn)(void*), void *stack, int flags, void *arg, pid_t *child_tid);
int sys_join_thread(pid_t tid, void **arg);
int sys_set_tls(void *tls);
#endif

#endif
