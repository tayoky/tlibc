#ifndef _SCHED_H
#define _SCHED_H

#include <sys/types.h>

int clone(int (*fn)(void*),void *stack,int flags,void *arg,pid_t *parent_tid,void *tls,pid_t *child_tid);

#define CLONE_THREAD 0x01


#endif