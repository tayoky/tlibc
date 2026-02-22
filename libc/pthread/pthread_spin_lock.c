#include <pthread.h>
#include <stdatomic.h>

//FIXME : there is no deadlock prevention here
//TODO : maybee yeld

int pthread_spin_lock(pthread_spinlock_t *lock){
    while(atomic_flag_test_and_set(lock));
    return 0;
}
