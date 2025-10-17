#include <pthread.h>

int pthread_attr_setguardsize(pthread_attr_t *attr, size_t guardsize){
    attr->guard_size = guardsize;
    return 0;
}