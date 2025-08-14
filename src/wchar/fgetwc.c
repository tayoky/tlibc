#include <wchar.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>

wint_t fgetwc(FILE *stream){
	//we can try with different sizes up to MB_CUR_MAX
	char buf[MB_CUR_MAX];
	wchar_t wc;
	for(size_t i=0; i<MB_CUR_MAX; i++){
		int c = fgetc(stream);
		if(c == EOF) return WEOF;
		buf[i] = (char)c;
		if(mbtowc(&wc,buf,i+1) >= 0){
			//valid wchar
			return wc;
		}
	}
	//invalid wchar
	stream->errno = errno;
	return WEOF;
}
