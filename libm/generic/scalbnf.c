#include <math.h>

float scalbnf(float x, int exp) {
	return ldexpf(x, exp);
}
