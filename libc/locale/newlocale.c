#include <locale-internal.h>
#include <stdlib.h>
#include <string.h>

locale_t newlocale(int mask, const char *locale, locale_t base) {
	if (base == NULL) {
		// start over the C locale
		base = (locale_t)&__c_locale;
	};

	if ((mask == LC_ALL_MASK && !strcmp(locale, "C")) || (mask == 0 && base == &__c_locale)) {
		// the result of this operation would be the C locale
		return (locale_t)&__c_locale;
	}

	if (mask == 0) {
		// nothing to change
		locale_t ret = malloc(sizeof(struct __locale));
		if (!ret) return NULL;
		*ret = *base;
		return ret;
	}

	// TODO : implement loading
	return NULL;
}
