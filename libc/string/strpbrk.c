#include <string.h>

char *strpbrk(const char *str,const char *search){
	while(*str){
		for (size_t i = 0; i < strlen(search); i++){
			if(*str == search[i]){
				return (char *)str;
			}
		}
		str++;
	}
	return NULL;
}
