#include <locale.h>

extern struct __locale _locale;

struct lconv *localeconv(void){
	return &_locale.lconv;
}
