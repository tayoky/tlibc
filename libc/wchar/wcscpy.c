#include <wchar.h>

wchar_t *wcscpy(wchar_t *dest,const wchar_t *src){
	wchar_t *dst = dest;
	while(*src){
		*dst = *src;
		src++;
		dst++;
	}
	return dest;
}
