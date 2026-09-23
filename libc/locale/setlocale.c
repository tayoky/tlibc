#include <locale.h>
#include <stdlib.h>
#include <string.h>

extern struct __locale _locale;

char *setlocale(int category, const char *locale) {
	if (category > LC_ALL || category < 0) return NULL;

	if (locale) {
		locale_t new_locale = NULL;
		if (category == LC_ALL) {
			new_locale = newlocale(LC_ALL_MASK, locale, &_locale)->locales[0]->name;
		} else {
			new_locale = newlocale(1 << category, locale, &_locale)->locales[category]->name;
		}
		if (!new_locale) return NULL;
		_locale = *new_locale;
	}

	if (category == LC_ALL) {
		return _locale.locales[0]->name;
	} else {
		return _locale.locales[category]->name;
	}
}
