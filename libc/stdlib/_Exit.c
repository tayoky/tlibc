#include <stdnoreturn.h>
#include <stdlib.h>
#include <unistd.h>

noreturn void _Exit(int status){
	_exit(status);
}
