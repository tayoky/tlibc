#include <pthread.h>

int pthread_attr_getstack(const pthread_attr_t *restrict attr,void **restrict stackaddr,size_t *restrict stacksize){
    if(stacksize)*stackaddr = attr->stack;
    if(stacksize)*stacksize = attr->stack_size;
    return 0;
}