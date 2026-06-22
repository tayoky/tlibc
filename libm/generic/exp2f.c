#include <math.h>
#include "internal.h"

static const float c[7] = {
    1.0f,
    0.69314718055994530942f,
    0.24022650695910071233f,
    0.05550410866482157995f,
    0.00961812910762847716f,
    0.00133335581464284434f,
    0.00015403530393381614,
};

float exp2f(float x) {
	if (isnan(x)) return x;
	if (x > 128.0f) return INFINITY;
	if (x < -150.0f) return 0.0f;

	float k = roundf(x);
	float r = x - k;

	float p = c[6];
	for (int i = 5; i >= 0; --i) {
		p = p * r + c[i];
	}
	return ldexpf(p, (int)k);
}
