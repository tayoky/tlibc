#include <pthread.h>
#include <stdatomic.h>

int pthread_spin_unlock(pthread_spinlock_t *lock){
    atomic_store(lock, 0);
    return 0;
}
