#include <string.h>

int strncmp(const char *str1,const  char *str2,size_t n){
	while (*str1 || *str2) {
		if(n-- <= 0){
			return 0;
		}
		if (*str1 != *str2) return *str1 - *str2;
		str1++;
		str2++;
	}
	return 0;
}
