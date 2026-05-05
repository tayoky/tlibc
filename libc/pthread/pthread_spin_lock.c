#include <pthread.h>
#include <stdatomic.h>

//FIXME : there is no deadlock prevention here
//TODO : maybee yeld

int pthread_spin_lock(pthread_spinlock_t *lock){
    while(atomic_exchange(lock, 1));
    return 0;
}
