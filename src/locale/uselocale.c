#include <locale.h>

extern struct __locale _locale;

locale_t uselocale(locale_t locale){
	if(locale){
		_locale = *locale;
	}
	return &_locale;
}
