#include <pthread.h>
#include <sched.h>
#include <stddef.h>
#include <stdlib.h>
#include <tlibc.h>
#include <sys/mman.h>
#include <stdint.h>

struct pthread_args {
	void *arg;
	void *(*start_routine)(void *);
	struct __uthread *uthread;
};

static int __pthread_creator(void *arg){
	struct pthread_args *_args = arg;
	struct pthread_args args = *_args;
	free(_args);

	stanix_set_tls(args.uthread);

	pthread_exit(args.start_routine(args.arg));
	return 0;
}

int pthread_create(pthread_t *thread,const pthread_attr_t *attr,void *(*start_routine)(void *),void *arg){
	struct pthread_args *args = malloc(sizeof(struct pthread_args));
	args->arg = arg;
	args->start_routine = start_routine;

	pthread_attr_t default_attr;
	if(!attr){
		pthread_attr_init(&default_attr);
		attr = &default_attr;
	}

	struct __uthread *uthread = __new_uthread();
	if(!uthread){
		free(args);
		return -1;
	}
	args->uthread = uthread;

	void *stack = attr->stack ? attr->stack : mmap(NULL,attr->stack_size,PROT_READ | PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS,0,0);
	if(stack == MAP_FAILED){
		__free_uthread(uthread);
		free(args);
		return -1;
	}
	uintptr_t stack_top = (uintptr_t)stack + attr->stack_size;
	// align the stack
	stack_top &= ~0xf;
	stack_top -= 8;

	return stanix_new_thread((void *)__pthread_creator,(void*)stack_top,0,args,thread);
}