#include <pthread.h>
#include <stdatomic.h>

int pthread_spin_unlock(pthread_spinlock_t *lock){
    atomic_flag_clear(lock);
    return 0;
}
