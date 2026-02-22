#include <stdlib.h>
#include <string.h>

void *calloc(size_t num,size_t size){
	size *= num;
	void *buf = malloc(size);
	if(buf)memset(buf,0,size);
	return buf;
}
