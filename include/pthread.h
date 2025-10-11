#ifndef _PTHREAD_H
#define _PTHREAD_H

#include <sys/types.h>

typedef struct __pthread {
	pid_t tid;
} pthread_t;

//idk
typedef int pthread_attr_t;

int pthread_create(pthread_t *thread,const pthread_attr_t *attr,typeof(void *(void *)) *start_routine,void *arg);
void pthread_exit(void *retval);

#endif