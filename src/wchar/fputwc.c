#include <wchar.h>
#include <stdio.h>
#include <limits.h>

wint_t fputwc(wchar_t wc,FILE *stream){
	char buf[MB_CUR_MAX];
	int len = wctomb(buf,wc);
	if(len < 0)return WEOF;
	return fwrite(buf,len,1,stream) ? wc : WEOF;
}
