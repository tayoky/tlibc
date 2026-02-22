#include <locale.h>
#include <string.h>
#include <stdlib.h>

extern struct __locale _locale;

static const char *type2name(int category){
	switch(category){
	case LC_ALL:
		return "LC_ALL";
	case LC_MONETARY:
		return "LC_MONETARY";
	case LC_NUMERIC:
		return "LC_NUMERIC";
	case LC_COLLATE:
		return "LC_COLLATE";
	case LC_CTYPE:
		return "LC_CTYPE";
	case LC_MESSAGES:
		return "LC_MESSAGES";
	case LC_TIME:
		return "LC_TIME";
	default:
		return NULL;
	}
}

char *setlocale(int category,const char *locale){
	if(category>LC_ALL)return NULL;

	if(category == LC_ALL){
		if (!locale) return _locale.locales[0]->name;
		return newlocale(LC_ALL_MASK, locale, &_locale)->locales[0]->name;
	} else {
		if (!locale) return _locale.locales[category]->name;
		return newlocale(1 << category, locale, &_locale)->locales[category]->name;
	}
}
