#include <unistd.h>

unsigned int sleep(unsigned int seconds){
	return usleep(seconds * 1000000);
}
