#include <math.h>

double copysign(double x, double y) {
    x = fabs(x);
    return y < 0 ? -x : x;
}
