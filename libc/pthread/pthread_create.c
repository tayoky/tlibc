#include <sys/mman.h>
#include <pthread.h>
#include <sysdeps.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <tlibc.h>

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
	sys_set_tls(args.uthread);

	pthread_exit(args.start_routine(args.arg));
	return 0;
}

#define PAGE_ALIGN_UP(x) ((((x) + PAGE_SIZE - 1) / PAGE_SIZE) * PAGE_SIZE)

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
		return errno;
	}
	args->uthread = uthread;

	void *stack = attr->stack;
	size_t stack_size;
	if (stack) {
		stack_size = attr->stack_size;
	} else {
		stack_size = PAGE_ALIGN_UP(attr->stack_size) + attr->guard_size;
		// allocate our own stack and guards
		stack = mmap(NULL, stack_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
		if (stack == MAP_FAILED) {
			__free_uthread(uthread);
			free(args);
			return errno;
		}

		// set the guards
		if (attr->guard_size > 0) {
			mprotect(stack, attr->guard_size, PROT_NONE);
		}
	}

	if (thread) *thread = uthread;

	uthread->stack = stack;
	uthread->stack_size = stack_size;
	uthread->stack_is_allocated = !attr->stack;
	uthread->detach_state = attr->detach_state;

	// align the stack
	uintptr_t stack_top = (uintptr_t)stack + stack_size;
	stack_top &= ~0xf;
	stack_top -= 8;

	int ret = sys_new_thread((void *)__pthread_creator, (void *)stack_top, 0, args, &uthread->tid);
	if (ret < 0) {
		if (uthread->stack_is_allocated) {
			munmap(uthread->stack, uthread->stack_size);
		}
		__free_uthread(uthread);
		free(args);
	}
	return ret;
}
