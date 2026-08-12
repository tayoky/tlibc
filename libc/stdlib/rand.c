#include <limits.h>
#include <stdlib.h>

static unsigned int s = 0;

int rand(void) {
	return rand_r(&s);
}

int rand_r(unsigned int *seedp) {
	unsigned int x = *seedp;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	*seedp = x;
	return x % RAND_MAX;
}

void srand(unsigned int seed) {
	s = seed;
}
