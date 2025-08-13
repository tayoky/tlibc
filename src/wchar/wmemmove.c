#include <wchar.h>
#include <string.h>

wchar_t *wmemmove(wchar_t *dest,const wchar_t *src,size_t n){
	return memmove(dest,src,n * sizeof(wchar_t));
}
