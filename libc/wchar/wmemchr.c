#include <wchar.h>

wchar_t *wmemchr(const wchar_t *ws,wchar_t wc,size_t n){
	while(n > 0){
		if(*ws == wc)return (wchar_t*)ws;
		n--;
		ws++;
	}
	return NULL;
}
