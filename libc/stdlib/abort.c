#include <stdlib.h>
#include <signal.h>

void abort(void){
	raise(SIGABRT);
	exit(EXIT_FAILURE);
}
