#include <math.h>
#include "internal.h"

float log2f(float n) {
    if (n <= 0.0f) return -INFINITY;

    unsigned int E, M;

    M = (*(unsigned int*) &n) & 0x007FFFFF; 
    E = ((*(unsigned int*) &n) >> 23) & 0xFF;

    return ((float) E) - 127.0f + logf2_01(M / 8388608.0f);
}


