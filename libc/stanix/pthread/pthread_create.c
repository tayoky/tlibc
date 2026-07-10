#include <sys/mman.h>
#include <pthread.h>
#include <sched.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <tlibc.h>

// do not compile this for dynamic linker
#ifndef __DL_TLIBC__

struct pthread_args {
	void *arg;
	void *(*start_routine)(void *);
	struct __uthread *uthread;
};

static int __pthread_creator(void *arg) {
	struct pthread_args *_args = arg;
	struct pthread_args args = *_args;
	free(_args);

	args.uthread->tid = gettid();
	stanix_set_tls(args.uthread);

	pthread_exit(args.start_routine(args.arg));
	return 0;
}

int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg) {
	struct pthread_args *args = malloc(sizeof(struct pthread_args));
	args->arg = arg;
	args->start_routine = start_routine;

	pthread_attr_t default_attr;
	if (!attr) {
		pthread_attr_init(&default_attr);
		attr = &default_attr;
	}

	struct __uthread *uthread = __new_uthread();
	if (!uthread) {
		free(args);
		return -1;
	}
	args->uthread = uthread;

	void *stack = attr->stack ? attr->stack : mmap(NULL, attr->stack_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	if (stack == MAP_FAILED) {
		__free_uthread(uthread);
		free(args);
		return -1;
	}

	if (thread) *thread = uthread;

	uthread->stack = stack;
	uthread->stack_size = attr->stack_size;
	uthread->stack_is_allocated = !attr->stack;
	uthread->detach_state = attr->detach_state;

	// align the stack
	uintptr_t stack_top = (uintptr_t)stack + attr->stack_size;
	stack_top &= ~0xf;
	stack_top -= 8;

	return stanix_new_thread((void *)__pthread_creator, (void *)stack_top, 0, args, NULL);
}
#endif
