#include <math.h>

long double fminl(long double a,long double b){
	return a < b ?  a : b;
}
long double fmaxl(long double a,long double b){
	return a > b ?  a : b;
}
