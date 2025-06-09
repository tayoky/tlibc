#ifndef _INTERNAL_H
#define _INTERNAL_H

#define template(type,name) static inline type log##name##2_01(type x) {\
    type x2 = x * x, x3 = x2 * x, x4 = x3 * x, x5 = x4 * x;\
\
    return 0.0426634327651f * x5 - 0.1860397355647f * x4 + 0.4075559395645f * x3 - 0.7055868559292f * x2 + 1.4414072191643f * x;\
}\
static inline type pow##name##2_01(type x) {\
    type x2 = x * x, x3 = x2 * x, x4 = x3 * x, x5 = x4 * x;\
\
    return 0.0018932135149f * x5 + 0.0089454792171f * x4 + 0.0558701110667f * x3 + 0.2401360232927f * x2 + 0.6931551729086f * x + 1.0f;\
}

template(float,f)
template(double,)
template(long double,l)

#undef template

#endif
