#define STUB(name) int name(){return 0;}

STUB(utime)
STUB(alarm)
STUB(popen)
STUB(pclose)
STUB(sched_yield)

STUB(pthread_cond_init)
STUB(pthread_cond_destroy)
STUB(pthread_cond_broadcast)
STUB(pthread_cond_signal)
STUB(pthread_cond_timedwait)
STUB(pthread_cond_wait)
STUB(pthread_detach)
STUB(pthread_key_create)
STUB(pthread_key_delete)
STUB(pthread_setspecific)
STUB(pthread_getspecific)
