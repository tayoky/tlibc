#include <pthread.h>
#include <sched.h>
#include <stddef.h>
#include <stdlib.h>

struct pthread_args {
	void *arg;
	void *(*start_routine)(void *);
};

static int __pthread_creator(void *arg){
	struct pthread_args *_args = arg;
	struct pthread_args args = *_args;
	free(_args);
	pthread_exit(args.start_routine(args.arg));
	return 0;
}

int pthread_create(pthread_t *thread,const pthread_attr_t *attr,void *(*start_routine)(void *),void *arg){
	struct pthread_args *args = malloc(sizeof(struct pthread_args));
	args->arg = arg;
	args->start_routine = start_routine;
	return clone((void *)__pthread_creator,NULL,CLONE_THREAD,args,NULL,NULL,&thread->tid);
}