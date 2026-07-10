#ifndef _SIGNAL_H
#define _SIGNAL_H

#include <sys/signal.h>

struct __uthread;
typedef struct __uthread *pthread_t;

int pthread_kill(pthread_t thread, int sig);
int pthread_sigmask(int how, const sigset_t *restrict set, sigset_t *restrict oldset);

#endif
