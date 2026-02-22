#include <string.h>

int memcmp(const void *buf1,const void *buf2,size_t count){
	while (count-- > 0){
		if(*(char *)buf1 != *(char *)buf2) return *(char *)buf1 - *(char *)buf2;
		(char *)buf1++;
		(char *)buf2++;
	}

	return 0;
}
