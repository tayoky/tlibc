#include <string.h>

void *memchr(const void *buf, int c, size_t count){
	while(count-- > 0){
		if(*(char *)buf == (char)c){
			return (void *)buf;
		}
		(char *)buf++;
	}
	return NULL;
}
