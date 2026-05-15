#include <locale.h>
#include <stdlib.h>
#include <string.h>

extern struct __locale _locale;

char *setlocale(int category, const char *locale) {
	if (category > LC_ALL) return NULL;

	if (category == LC_ALL) {
		if (!locale) return _locale.locales[0]->name;
		return newlocale(LC_ALL_MASK, locale, &_locale)->locales[0]->name;
	} else {
		if (!locale) return _locale.locales[category]->name;
		return newlocale(1 << category, locale, &_locale)->locales[category]->name;
	}
}
