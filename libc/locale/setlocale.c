#include <locale-internal.h>
#include <stdlib.h>
#include <string.h>

static char *lc_all_name;

char *setlocale(int category, const char *locale) {
	if (category > LC_IDENTIFICATION || category < 0) return NULL;

	if (!locale) {
		if (category == LC_ALL) return lc_all_name ? lc_all_name : "C";
		return (char*)__global_locale->data[category]->name;
	}

	if (!strcmp(locale, "POSIX")) locale = "C";
	(void)locale;
	if (strcmp(locale, "C") && strcmp(locale, "")) return NULL;
	return "C";

	// we only support the C locale for now
	// TODO : load locales and compute LC_ALL name
}
