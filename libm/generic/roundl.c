#include <math.h>

long double roundl(long double x){
	return floorl(x + 0.5f);
}
