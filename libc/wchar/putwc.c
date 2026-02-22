#include <wchar.h>

wint_t putwc(wchar_t wc,FILE *stream){
	return fputwc(wc,stream);
}
