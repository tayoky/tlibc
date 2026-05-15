#include <stdlib.h>

ldiv_t ldiv(long int number, long int denom) {
	return (ldiv_t){
		.quot = number / denom,
		.rem = number % denom,
	};
}
