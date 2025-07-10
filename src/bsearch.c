#include <stdlib.h>
#include <stdint.h>

#define e(i) ((void *)((uintptr_t)base + (i) * size))

void *bsearch(const void *key, const void *base, size_t n, size_t size, int (*compar)(const void *,const void *)){
	if(!n || !size)return NULL;
	size_t start = 0;
	size_t end = n - 1;

	while(start <= end){
		int i = (end + start)/2;
		int cmp = compar(key,e(i));
		if(cmp == 0)return e(i);
		if(cmp > 0){
			start = i + 1;
		} else {
			if(i == 0)return NULL;
			end   = i - 1;
		}
	}
	return NULL;
}
