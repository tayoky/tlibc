#include <wchar.h>
#include <stdio.h>

//FIXME : this should use wctomb
wint_t fputwc(wchar_t wc,FILE *stream){
	return fwrite(&wc,sizeof(wchar_t),1,stream) ? wc : WEOF;
}
