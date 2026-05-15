#include <errno.h>
#include <pthread.h>
#include <stdatomic.h>

int pthread_spin_trylock(pthread_spinlock_t *lock) {
	return atomic_exchange(lock, 1) ? EBUSY : 0;
}
