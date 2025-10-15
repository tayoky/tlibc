#ifndef _SCHED_H
#define _SCHED_H

#include <sys/types.h>

int stanix_new_thread(void (*fn)(void*),void *stack,int flags,void *arg,void *tls,pid_t *child_tid);


#endif