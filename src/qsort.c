#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define e(i) ((void *)((uintptr_t)base + (i) * size))
#define compare(e1,e2) compar(e(e1),e(e2),arg)
#define swap(e1,e2) _swap(e(e1),e(e2),size)
static inline void _swap(void *e1,void *e2,size_t size){
	char tmp[size];
	memcpy(tmp,e2,size);
	memcpy(e2,e1,size);
	memcpy(e1,tmp,size);
}

void qsort_r(void *base,size_t n,size_t size,int (*compar)(const void*,const void *,void *),void *arg){
	if(!size || !n)return;
	size_t pivot = n - 1;
	size_t j = 0;
	for(size_t i=0; i<pivot; i++){
		if(compare(i,pivot) <= 0){
			swap(i,j);
			j++;
		}
	}
	swap(j,pivot);
	pivot = j;

	//now everything inferior to pivot is at the left
	//and everything superior at the righr
	if(pivot > 1)qsort_r(base,pivot,size,compar,arg);
	if(pivot < n-2)qsort_r(e(pivot+1),n-pivot-1,size,compar,arg);
}


void qsort(void *base,size_t n,size_t size,int (*compar)(const void*,const void *)){
	//we use cast to void to avoid warning
	return qsort_r(base,n,size,(void *)compar,NULL);
}
