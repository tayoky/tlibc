#include <locale.h>
#include <string.h>
#include <stdlib.h>

extern struct __locale _locale;
extern const struct __locale __posix;

//by default we use posix locale
//this array is here cause no other function need to know locale name
static const char *conv[LC_ALL] = {
	"POSIX",
	"POSIX",
	"POSIX",
	"POSIX",
	"POSIX",
	"POSIX",
};

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
		setlocale(LC_COLLATE,locale);
		setlocale(LC_CTYPE,locale);
		setlocale(LC_MONETARY,locale);
		setlocale(LC_MESSAGES,locale);
		setlocale(LC_NUMERIC,locale);
		return setlocale(LC_TIME,locale);
	}
	if(!locale){
		//just fetch
		return (char *)conv[category];
	}

	if(locale[0] == '\0'){
		//no locale ??? try to get from environ
		if(getenv("LC_ALL")){
			locale = getenv("LC_ALL");
		} else if(getenv(type2name(category))){
			locale = getenv(type2name(category));
		} else if(getenv("LANG")){
			locale = getenv("LANG");
		}
	}

	//locale "C" is same as "POSIX"
	if(!strcmp(locale,"C"))locale = "POSIX";

	//TODO : load locale file
	if(strcmp(locale,"POSIX"))return NULL;
	conv[category] = locale;


	struct __locale l = __posix;
	switch(category){
	case LC_CTYPE:
		memcpy(_locale.ctype,l.ctype,sizeof(l.ctype));
		memcpy(_locale.tolower,l.tolower,sizeof(l.tolower));
		memcpy(_locale.toupper,l.toupper,sizeof(l.toupper));
		break;
	case LC_NUMERIC:
		memcpy(_locale.lconv.decimal_point,l.lconv.decimal_point,sizeof(_locale.lconv.decimal_point));
		memcpy(_locale.lconv.thousands_sep,l.lconv.thousands_sep,sizeof(_locale.lconv.thousands_sep));
		memcpy(_locale.lconv.grouping,l.lconv.grouping,sizeof(_locale.lconv.grouping));
		break;
	case LC_TIME:
		_locale.time = l.time;
		break;
	case LC_MESSAGES:
		_locale.messages = l.messages;
		break;
	}

	return (char *)locale;
}
