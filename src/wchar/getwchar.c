#include <wchar.h>

wint_t getwchar(void){
	return fgetwc(stdin);
}
