#include <math.h>

void sincosf(float x, float *sin, float *cos) {
	*sin = sinf(x);
	*cos = cosf(x);
}
