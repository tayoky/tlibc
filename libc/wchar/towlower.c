#include <wchar.h>

wint_t towlower(wint_t wc){
	if(wc >= L'A' && wc <= L'Z'){
		return wc - L'A' + L'a';
	}
	return wc;
}
