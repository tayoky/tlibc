#include <wchar.h>

wchar_t *wmemset(wchar_t *ws,wchar_t wc,size_t n){
	wchar_t *dest = ws;
	while(n > 0){
		*ws = wc;
		n--;
		ws++;
	}
	return dest;
}
