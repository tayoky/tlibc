#include <stdlib.h>

lldiv_t lldiv(long long number, long long denom) {
	return (lldiv_t){
		.quot = number / denom,
		.rem = number % denom,
	};
}
