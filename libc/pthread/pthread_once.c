#include <pthread.h>
#include <stdatomic.h>

int pthread_once(pthread_once_t *once_control, void (*init_routine)(void)){
    if(atomic_flag_test_and_set(once_control)){
        //the flag was already set
        return 0;
    }

    init_routine();
    return 0;
}
