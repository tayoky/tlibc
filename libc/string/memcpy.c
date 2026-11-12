#include <string.h>
#include <stdint.h>

// we keep this two together, so the compiler can inline memcpy in memmove

void *memcpy(void *dest, const void *src, size_t n) {
	void *prev = dest;
#if defined(__x86_64__) || defined(__i386__)
	asm volatile("rep movsb" : "+D"(dest), "+S"(src), "+c"(n) : : "memory");
#else
	char *cdest = dest;
	const char *csrc = src;
	while (n > 0) {
		*cdest = *csrc;
		cdest++;
		csrc++;
		n--;
	}
#endif
	return prev;
}

void *memmove(void *dest, const void *src, size_t n) {
	if ((uintptr_t)dest == (uintptr_t)src) {
		return dest;
	}

	if ((uintptr_t)dest < (uintptr_t)src) {
		return memcpy(dest, src, n);
	}

#if defined(__x86_64__) || defined(__i386__)
	void *prev = dest;
	asm volatile("std \n rep movsb \n cld" : "=D"(dest), "=S"(src), "+c"(n) : "D"((char *)dest + n - 1), "S"((char *)src + n - 1) : "memory");
	return prev;
#else
	while (n > 0) {
		n--;
		((char *)dest)[n] = ((char *)src)[n];
	}
	return dest;
#endif
}
