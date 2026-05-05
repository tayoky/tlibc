#include <pthread.h>
#include <stdatomic.h>

int pthread_spin_init(pthread_spinlock_t *lock, int pshared){
    (void)pshared;
    atomic_store(lock, 0);
    return 0;
}
