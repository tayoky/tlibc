#include <string.h>
#include <ctype.h>

int strcasecmp(const char *str1, const char *str2){
	while (*str1 || *str2) {
		int c1 = tolower(*(unsigned char *)str1);
		int c2 = tolower(*(unsigned char *)str2);
		if (c1 != c2) return c1 - c2;
		str1++;
		str2++;
	}
	return 0;
}
