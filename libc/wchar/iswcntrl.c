#include <wchar.h>

int iswcntrl(wint_t wc){
	//maybee there are others ???
	return (wc >= 0 && wc <= 32) || wc == 0x7f;
}
