#include <wchar.h>

int iswlower(wint_t wc){
	return wc >= L'a' && wc <= L'z';
}
