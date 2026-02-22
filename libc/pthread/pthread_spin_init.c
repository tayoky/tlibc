#include <pthread.h>
#include <stdatomic.h>

int pthread_spin_init(pthread_spinlock_t *lock, int pshared){
    (void)pshared;
    atomic_flag_clear(lock);
    return 0;
}
