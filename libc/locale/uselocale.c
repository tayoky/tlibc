#include <locale-internal.h>
#include <tlibc.h>

locale_t uselocale(locale_t locale) {
	locale_t old = _NL_CURRENT_LOCALE;
	if (locale) {
		__get_uthread()->locale = locale == LC_GLOBAL_LOCALE ? NULL : locale;
	}
	return old == __global_locale ? LC_GLOBAL_LOCALE : old;
}
