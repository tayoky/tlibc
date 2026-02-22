#include <pthread.h>

int pthread_attr_getstacksize(const pthread_attr_t *restrict attr,size_t *restrict stacksize){
    *stacksize = attr->stack_size;
    return 0;
}
