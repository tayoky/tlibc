#include <math.h>

long double copysignl(long double x, long double y) {
    x = fabsl(x);
    return y < 0 ? -x : x;
}
