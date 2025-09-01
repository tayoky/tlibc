#include <string.h>

char *strncat(char *dest,const char *src,size_t n){
	char *dst = dest;
	while(*dest)dest++;

	while(n-- > 0 && *src){
		*(dest++) = *(src++);
	}

	*dest = '\0';
	return dst;
}
