#include <string.h>
#include <stdint.h>

size_t strnlen(const char *str,size_t maxlen){
	const char *end = memchr(str,'\0',maxlen);
	return end ? (uintptr_t)end - (uintptr_t)str : maxlen;
}
