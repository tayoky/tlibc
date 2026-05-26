#include <math.h>

float copysignf(float x, float y) {
    x = fabsf(x);
    return y < 0 ? -x : x;
}
