#include <locale.h>
#include <langinfo.h>
#include <stdlib.h>
#include <string.h>

static struct __locale _locale;
static const char *conv[LC_ALL];

static struct __locale posix = {
	.lconv = {
		.decimal_point = ".",
		.thousands_sep = "",
		.grouping = {-1},
	},
	.time = {
		.am = "AM",
		.pm = "PM",
		.day = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"},
		.abday = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"},
		.mon = {"January","February","March","April","Mai","June","July","August","September","October","November","December"},
		.abmon = {"Jan","Feb","Mar","Apr","Mai","Jun","Jul","Aug","Sep","Oct","Nov","Dec"},
		.d_t_fmt = "%a %b %e %H:%M:%S %Y",
		.d_fmt = "%m/%d/%y",
		.t_fmt = "%H:%M:%S",
		.t_fmt_ampm = "%l:%M:%S %p",
	},
	.messages = {
		.yesexpr = "^[yY]",
		.noexpr  = "^[nN]",
	},
};

struct lconv *localeconv(void){
	return &_locale.lconv;
}

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

	//locale "C" is same as "POSIX"
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

	if(!strcmp(locale,"POSIX"))return NULL;
	conv[category] = locale;


	//TODO : read config files
	struct __locale l = posix;
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

char *nl_langinfo(nl_item item){
	return nl_langinfo_l(item,&_locale);
}
char *nl_langinfo_l(nl_item item, locale_t locale){
	if(item >= DAY_1 && item <= DAY_7){
		return locale->time.day[item-DAY_1];
	}
	if(item >= ABDAY_1 && item <= ABDAY_7){
		return locale->time.day[item-ABDAY_1];
	}
	if(item >= MON_1 && item <= MON_12){
		return locale->time.day[item-MON_1];
	}
	if(item >= ABMON_1 && item <= ABMON_12){
		return locale->time.day[item-ABMON_1];
	}

	switch(item){
	//LC_NUMERIC
	case RADIXCHAR:
		return locale->lconv.decimal_point;
	case THOUSEP:
		return locale->lconv.thousands_sep;
	//LC_TIME
	case D_T_FMT:
		return locale->time.d_t_fmt;
	case D_FMT:
		return locale->time.d_fmt;
	case T_FMT:
		return locale->time.t_fmt;
	case T_FMT_AMPM:
		return locale->time.t_fmt_ampm;
	case AM_STR:
		return locale->time.am;
	case PM_STR:
		return locale->time.pm;
	//LC_MESSAGES
	case YESEXPR:
		return locale->messages.yesexpr;
	case NOEXPR:
		return locale->messages.noexpr;
	default:
		return NULL;
	}
}
