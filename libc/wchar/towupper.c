#include <wchar.h>

wint_t towupper(wint_t wc){
	if(wc >= L'a' && wc <= L'z'){
		return wc - L'a' + L'A';
	}
	return wc;
}
