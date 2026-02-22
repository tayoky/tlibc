#include <string.h>

char *strrchr(const char *str, int c){
	const char *best = NULL;
	while(*str){
		if(*str == (char)c)best = str;
		str++;
	}
	if((char)c == 0)return (char *)str;
	return (char *)best;
}
