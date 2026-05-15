#include <limits.h>
#include <pthread.h>
#include <stddef.h>

int pthread_attr_init(pthread_attr_t *attr) {
	attr->stack_size = 64 * 1024;
	attr->stack = NULL;
	attr->guard_size = PAGE_SIZE;
	return 0;
}
