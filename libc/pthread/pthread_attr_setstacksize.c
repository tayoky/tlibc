#include <pthread.h>

int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize){
    attr->stack_size = stacksize;
    return 0;
}
