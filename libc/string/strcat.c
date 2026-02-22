#include <string.h>

char *strcat(char * dest, const char * src){
	char *dst = dest;
	while(*dst)dst++;
	strcpy(dst,src);
	return dest;
}
