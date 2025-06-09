#include <math.h>
#include <stdint.h>
#include "internal.h"

float powf(float n, float p) {
    unsigned int E, M;

    M = (*(unsigned int*) &n) & 0x007FFFFF; 
    E = ((*(unsigned int*) &n) >> 23) & 0xFF;

    if (E == 0) return 0.0f;

    float new_exp = (((float) E) - 127.0f + log2_01(M / 8388608.0f)) * p;

    int newE = (new_exp < 0? new_exp - 1.0f : new_exp) + 127 + (new_exp < 0.0f);

    float fracPart = (new_exp - ((float) (int) new_exp)) + (new_exp < 0.0f);
    
    int newM = (powf2_01(fracPart) - 1.0f) * 8388608.0f;

    uint32_t result = ((newE & 0xFF) << 23) | (newM & 0x007FFFFF);

    float signP = n > 0.0f? 1.0f : -1.0f;

    return (*(float*) &result) * (((int) p) % 2? signP : 1.0f);
}
