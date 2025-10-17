#include <pthread.h>

int pthread_attr_setstack(pthread_attr_t *attr,void *stackaddr,size_t stacksize){
    attr->stack_size = stacksize;
    attr->stack = stackaddr;
    return 0;
}
