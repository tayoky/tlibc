#include <wchar.h>
#include <stdio.h>
#include <string.h>

wint_t btowc(int c){
	if(c >= 0 && c < 0x80){
		return c;
	} else {
		return WEOF;
	}
}

wint_t fputwc(wchar_t wc,FILE *stream){
	return fwrite(&wc,sizeof(wchar_t),1,stream) ? wc : WEOF;
}

int fputws(const wchar_t *ws,FILE *stream){
	return fwrite(ws,sizeof(ws),wcslen(ws),stream) ? 0 : -1;
}

wint_t putwc(wchar_t wc,FILE *stream){
	return fputwc(wc,stream);
}

wint_t putwchar(wchar_t wc){
	return fputwc(wc,stdout);
}

wchar_t *wcscat(wchar_t *dest,const wchar_t *src){
	wchar_t *dst = dest;
	while(*dst)dst++;
	wcscpy(dst,src);
	return dst;
}

wchar_t *wcschr(const wchar_t *ws,wchar_t wc){
	while(*ws){
		if(*ws == wc)return (wchar_t *)ws;
		ws++;
	}
	return NULL;
}

int wcscmp(const wchar_t *ws1,const wchar_t *ws2){
	while(*ws1 || *ws2){
		if(*ws1 != *ws2)return *ws1 > *ws2 ? 1 : -1;
		ws1++;
		ws2++;
	}
	return 0;
}

wchar_t *wcscpy(wchar_t *dest,const wchar_t *src){
	wchar_t *dst = dest;
	while(*src){
		*dst = *src;
		src++;
		dst++;
	}
	return dest;
}

size_t wcslen(const wchar_t *ws){
	size_t size = 0;
	while(*ws){
		ws++;
		size++;
	}
	return size;
}

wchar_t *wmemchr(const wchar_t *ws,wchar_t wc,size_t n){
	while(n > 0){
		if(*ws == wc)return (wchar_t*)ws;
		n--;
		ws++;
	}
	return NULL;
}

int wmemcmp(const wchar_t *ws1,const wchar_t *ws2,size_t n){
	while(n > 0){
		if(*ws1 != *ws2)return *ws1 > *ws2 ? 1 : -1;
		n--;
		ws1++;
		ws2++;
	}
	return 0;
}

wchar_t *wmemcpy(wchar_t *dest,const wchar_t *src,size_t n){
	return memcpy(dest,src,n * sizeof(wchar_t));
}

wchar_t *wmemmove(wchar_t *dest,const wchar_t *src,size_t n){
	return memmove(dest,src,n * sizeof(wchar_t));
}


wchar_t *wmemset(wchar_t *ws,wchar_t wc,size_t n){
	wchar_t *dest = ws;
	while(n > 0){
		*ws = wc;
		n--;
		ws++;
	}
	return dest;
}
