#include <stdlib.h>
#include <limits.h>

static unsigned int s = 0;

int rand(void){
	return rand_r(&s);
}

int rand_r(unsigned int *seedp){
	*seedp = *seedp * 18483838 + 12345;
	return *seedp%RAND_MAX;
}
void srand(unsigned int seed){
	s = seed;
}
