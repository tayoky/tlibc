#include "inttypes.h"

intmax_t imaxabs(intmax_t j) {
	intmax_t mask = j >> 63;
	return (j + mask) ^ mask;
}

imaxdiv_t imaxdiv(intmax_t numer, intmax_t denom) {
	imaxdiv_t result;
	result.quot = numer / denom;
	result.rem = numer % denom;
	return result;
}
