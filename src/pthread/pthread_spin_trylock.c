#include <pthread.h>
#include <stdatomic.h>
#include <errno.h>

int pthread_spin_trylock(pthread_spinlock_t *lock){
    return atomic_flag_test_and_set(lock) ? EBUSY : 0; 
}
