#ifndef _SCHED_H
#define _SCHED_H

#include <sys/types.h>

struct sched_param {
	int sched_priority;
};

#define SCHED_OTHER 0
#define SCHED_RR    1
#define SCHED_FIFO  2

int sched_get_priority_max(int policy);
int sched_get_priority_min(int policy);
int stanix_new_thread(void (*fn)(void*),void *stack,int flags,void *arg,pid_t *child_tid);
int stanix_join_thread(pid_t tid, void **arg);
int stanix_set_tls(void *tls);
int sched_yield(void);

#define __set_tls stanix_set_tls

#endif