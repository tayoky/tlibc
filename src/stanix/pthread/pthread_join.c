#include <pthread.h>
#include <sched.h>

int pthread_join(pthread_t thread, void **arg){
	return stanix_join_thread(thread, arg);
}