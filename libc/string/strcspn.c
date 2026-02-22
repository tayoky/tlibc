#include <string.h>

size_t strcspn(const char *str, const char *rej){
	size_t len = 0;
	while(*str){
		for(size_t i=0;rej[i];i++){
			if(*str == rej[i]){
				return len;
			}
		}
		str++;
		len++;
	}
	return len;
}
