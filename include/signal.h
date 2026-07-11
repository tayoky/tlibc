#ifndef _SIGNAL_H
#define _SIGNAL_H

#include <abi/signal.h>
#include <sys/types.h>

struct __uthread;
typedef struct __uthread *pthread_t;

int pthread_kill(pthread_t thread, int sig);
int pthread_sigmask(int how, const sigset_t *restrict set, sigset_t *restrict oldset);

int sigaddset(sigset_t *sigset, int signum);
int sigdelset(sigset_t *sigset, int signum);
int sigemptyset(sigset_t *sigset);
int sigfillset(sigset_t *sigset);
int sigismember(const sigset_t *set, int signum);
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
int sigpending(sigset_t *set);
int sigsuspend(const sigset_t *mask);
int sigwait(const sigset_t *set, int *sig);
int kill(pid_t pid, int sig);
int raise(int sig);
int sigaction(int signum, const struct sigaction *act,struct sigaction * oldact);
sighandler_t signal(int signum, sighandler_t handler);

#endif
