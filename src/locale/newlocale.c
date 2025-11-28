#include <locale.h>
#include <stdlib.h>

extern struct __locale _locale;

locale_t newlocale(int mask, const char *locale, locale_t base) {
	struct __locale_data *l = __findlocale(locale);
	if (!l) return NULL;

	if (base == NULL) {
		base = malloc(sizeof(struct __locale));
		base->allocated = 1;
		for (int i=0; i<LC_ALL; i++) {
			base->locales[i] = &__posix;
		}
	}

	for (int i=0; i<LC_ALL; i++) {
		if (mask & (1 << i)) {
			base->locales[i] = l;
		}
	}
	return base;
}
