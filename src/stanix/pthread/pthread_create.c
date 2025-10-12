#include <pthread.h>
#include <sched.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/mman.h>

#define STACK_SIZE 64 * 1024

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
	void *stack = mmap(NULL,STACK_SIZE,PROT_READ | PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS,0,0);
	if(stack == MAP_FAILED)return -1;
	return clone((void *)__pthread_creator,stack,CLONE_THREAD,args,NULL,NULL,thread);
}