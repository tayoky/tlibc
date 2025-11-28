#include <locale.h>

extern struct __locale _locale;

locale_t uselocale(locale_t locale){
	if(locale){
		_locale = *locale;
		_locale.allocated = 0;
	}
	return &_locale;
}
