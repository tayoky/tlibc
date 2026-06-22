#include <math.h>
#include "internal.h"

static const double c[7] = {
    1.0,
    0.69314718055994530942,
    0.24022650695910071233,
    0.05550410866482157995,
    0.00961812910762847716,
    0.00133335581464284434,
    0.00015403530393381614,
};

double exp2(double x) {
	if (isnan(x)) return x;
	if (x > 1023.0) return INFINITY;
	if (x < -1075.0) return 0.0;

	double k = round(x);
	double r = x - k;

	double p = c[6];
	for (int i = 5; i >= 0; --i) {
		p = p * r + c[i];
	}
	return ldexp(p, (int)k);
}
