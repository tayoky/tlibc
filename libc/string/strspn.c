#include <string.h>

size_t strspn(const char *str, const char *accept){
	size_t len = 0;
	while(*str){
		for(size_t i=0;accept[i];i++){
			if(*str == accept[i]){
				goto cont;
			}
		}
		return len;
cont:
		str++;
		len++;
		continue;
	}
	return len;
}
