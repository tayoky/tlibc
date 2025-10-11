#include <pthread.h>
#include <sched.h>
#include <stddef.h>

int pthread_create(pthread_t *thread,const pthread_attr_t *attr,typeof(void *(void *)) *start_routine,void *arg){
	return clone((void *)start_routine,NULL,CLONE_THREAD,arg,NULL,NULL,&thread->tid);
}