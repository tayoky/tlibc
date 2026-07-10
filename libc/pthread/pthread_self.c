#include <pthread.h>
#include <tlibc.h>

pthread_t pthread_self(void) {
	return __get_uthread();
}
