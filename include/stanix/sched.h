#ifndef _SCHED_H
#define _SCHED_H

#include <sys/types.h>

int stanix_new_thread(void (*fn)(void*),void *stack,int flags,void *arg,pid_t *child_tid);
int stanix_join_thread(pid_t tid, void **arg);
int stanix_set_tls(void *tls);

#define __set_tls stanix_set_tls

#endif