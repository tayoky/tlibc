#include <string.h>

char *strchr(const char *str, int c){
	while(*str){
		if(*str == (char)c){
			return (char *)str;
		}
		str++;
	}
	if(!c)return (char *)str;
	return NULL;
}
