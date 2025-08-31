#include <string.h>

char *strncpy(char *dest, const char *src,size_t n){
	char *d = dest;
	while (n > 0 && *src){
		*(dest++) = *(src++);
		n--;
	}

	while(n > 0){
		*(dest++) = '\0';
		n--;
	}
	return d;
}
