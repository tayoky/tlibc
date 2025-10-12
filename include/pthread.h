#ifndef _PTHREAD_H
#define _PTHREAD_H

#include <sys/types.h>

typedef pid_t pthread_t;

//idk
typedef int pthread_attr_t;

int pthread_create(pthread_t *thread,const pthread_attr_t *attr,void *(*start_routine)(void *),void *arg);
void pthread_exit(void *retval);

#endif