#include <wchar.h>

wchar_t *wcscat(wchar_t *dest,const wchar_t *src){
	wchar_t *dst = dest;
	while(*dst)dst++;
	wcscpy(dst,src);
	return dest;
}
