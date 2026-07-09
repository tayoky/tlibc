#include <math.h>

float scalblnf(float x, long exp) {
	return ldexpf(x, exp);
}
