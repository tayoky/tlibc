#include <ctype.h>
#include <string.h>

int strncasecmp(const char *str1, const char *str2, size_t n) {
	while (n > 0 && (*str1 || *str2)) {
		int c1 = tolower(*(unsigned char *)str1);
		int c2 = tolower(*(unsigned char *)str2);
		if (c1 != c2) return c1 - c2;
		str1++;
		str2++;
		n--;
	}
	return 0;
}
