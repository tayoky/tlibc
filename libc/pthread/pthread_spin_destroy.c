#include <pthread.h>

int pthread_spin_destroy(pthread_spinlock_t *lock){
    (void)lock;
    return 0;
}
