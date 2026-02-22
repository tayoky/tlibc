#include <string.h>

char *strcpy(char *dest, const char *src){
	char *d = dest;
	while (*src){
		*(dest++) = *(src++);
	}
	*dest = '\0';
	return d;
}
