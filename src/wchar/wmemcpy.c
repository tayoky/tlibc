#include <wchar.h>
#include <string.h>

wchar_t *wmemcpy(wchar_t *dest,const wchar_t *src,size_t n){
	return memcpy(dest,src,n * sizeof(wchar_t));
}
