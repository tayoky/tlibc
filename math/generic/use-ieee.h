#ifndef USE_IEEE754

#if __STDC_VERSION__ >= 202311L
//using c23 or higer
#ifdef __STDC_IEC_60559_BFP__
#define USE_IEEE754
#endif
#else
#ifdef __STDC_IEC_559__
#define USE_IEEE754
#endif
#endif

#endif
