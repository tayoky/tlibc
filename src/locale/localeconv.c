#include <locale.h>

extern struct __locale _locale;

struct lconv *localeconv(void){
	return (struct lconv*)&_locale.locales[LC_NUMERIC]->lconv;
}
