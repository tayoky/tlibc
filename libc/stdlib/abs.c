#include <limits.h>
#include <stdlib.h>


#define xabs(type, name) \
	type name(type x) { \
		type mask = x >> ((sizeof(type) * CHAR_BIT) - 1); \
		return (x ^ mask) - mask; \
	}

xabs(int, abs) xabs(long, labs) xabs(long long, llabs)
