#include <wchar.h>

wint_t putwchar(wchar_t wc){
	return fputwc(wc,stdout);
}
