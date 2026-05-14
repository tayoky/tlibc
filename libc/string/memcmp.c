#include <string.h>

int memcmp(const void *buf1, const void *buf2, size_t count) {
	const char *str1 = buf1;
	const char *str2 = buf2;
	while (count-- > 0) {
		if(*str1 != *str2) return *str1 - *str2;
		str1++;
		str2++;
	}

	return 0;
}
