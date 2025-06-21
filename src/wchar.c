#include <wchar.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

wint_t btowc(int c){
	if(c < 0){
		return WEOF;
	} else if(c <= 0x7f){
		return c;
	} else if(c <= 0x7ff){
		const uint8_t b1 = (1<<7) | (c & 0x3f);
		const uint8_t b2 = (3<<6) | ((c >> 6) & 0x1f);
		return (b2 << 8) | b1;
	} else {
		return WEOF;
	}
}

//simple mbtowc for utf8
#define S_CHECK(c) ((c & (3<<6)) == 1<<7)
int mbtowc(wchar_t *dest,const char *src,size_t n){
	if(!src||n==0)return 0;
	int len;
	if(n >= 1 && src[0] <= 0x7F){
		len = 1;
	} else if(n >= 2 && (src[0] & 0xE0) == 0xC0 && S_CHECK(src[1])){
		len = 2;
	} else if(n >= 3 && (src[0] & 0xF0) == 0xE0 && S_CHECK(src[1]) && S_CHECK(src[2])){
		len = 3;
	} else if(n >= 4 && (src[0] & 0xF8) == 0xF0 && S_CHECK(src[1]) && S_CHECK(src[2]) && S_CHECK(src[3])){
		len = 4;
	} else {
		errno = EILSEQ;
		return -1;
	}

	if(!dest)return len;

	int shift = 0;
	*dest = 0;
	for(int i=len-1; i>0; i--){
		*dest |= (src[i] & 0x3F) << shift;
		shift += 6;
	}

	*dest |= (src[0] & (0x7F >> (len-1))) << shift;
	return len;

}
size_t mbstowcs(wchar_t *dest,const char *src,size_t n){
	size_t len = 0;
	while(*src && n > 0){
		int len = mbtowc(dest,src,4);
		if(len < 0)return (size_t)-1;
		src+=len;
		n--;
		dest++;
	}
	if(n > 0)*dest = 0;
	return len;
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
