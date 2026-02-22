#include <pthread.h>

int pthread_attr_getguardsize(const pthread_attr_t *restrict attr,size_t *restrict guardsize){
    *guardsize = attr->guard_size;
    return 0;
}