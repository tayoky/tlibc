#include <string.h>

//we keep this two togher, so the compiler can inline memcpy in memmove

void *memcpy(void *dest, const void *src,size_t n){
	void *prev = dest;
#if defined(__x86_64__) || defined(__i386__)
	asm volatile("rep movsb"
		: "+D" (dest),
		  "+S" (src),
		  "+c" (n));
#else
	while(n > 0){
		*(char *)dest = *(char *)src;
		(char *)dest++;
		(char *)src++;
		n--;
	}
#endif
	return prev;
}

void *memmove(void *dest, const void *src, size_t n){
	if(dest == src){
		return dest;
	}

	if(dest < src){
		return memcpy(dest,src,n);
	}

#if defined(__x86_64__) || defined(__i386__)
	void *prev = dest;
	asm volatile("std \n rep movsb \n cld"
		: "=D" (dest),
		  "=S" (src),
		  "+c" (n)
		: "D" ((char *)dest + n - 1),
		  "S" ((char *)src  + n - 1));
	return prev;
#else
	while(n < 0){
		n--;
		((char *)dest)[n] = ((char *)src)[n];
	}
	return dest;
#endif
}
