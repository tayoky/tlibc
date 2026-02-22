#include <wchar.h>

size_t mbstowcs(wchar_t *dest,const char *src,size_t n){
	size_t len = 0;
	while(*src && n > 0){
		int len = mbtowc(dest,src,4);
		if(len < 0)return (size_t)-1;
		src+=len;
		n--;
		if(dest)dest++;
	}
	if(n > 0 && dest)*dest = 0;
	return len;
}
