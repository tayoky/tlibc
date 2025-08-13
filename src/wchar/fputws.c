#include <wchar.h>
#include <stdio.h>

//FIXME : this should use wcstombs
int fputws(const wchar_t *ws,FILE *stream){
	return fwrite(ws,sizeof(ws),wcslen(ws),stream) ? 0 : -1;
}
