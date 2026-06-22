#ifndef _SIGNAL_H
#define _SIGNAL_H

#include <sys/signal.h>

int pthread_sigmask(int how, const sigset_t *restrict set, sigset_t *restrict oldset);

#endif
