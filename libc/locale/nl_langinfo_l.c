#include <locale.h>
#include <langinfo.h>

char *nl_langinfo_l(nl_item item, locale_t locale){
	const struct __locale_data **l = locale->locales;
	if(item >= DAY_1 && item <= DAY_7){
		return (char*)l[LC_TIME]->time.day[item-DAY_1];
	}
	if(item >= ABDAY_1 && item <= ABDAY_7){
		return (char*)l[LC_TIME]->time.abday[item-ABDAY_1];
	}
	if(item >= MON_1 && item <= MON_12){
		return (char*)l[LC_TIME]->time.mon[item-MON_1];
	}
	if(item >= ABMON_1 && item <= ABMON_12){
		return (char*)l[LC_TIME]->time.abmon[item-ABMON_1];
	}

	switch(item){
	//LC_NUMERIC
	case RADIXCHAR:
		return (char*)l[LC_NUMERIC]->lconv.decimal_point;
	case THOUSEP:
		return (char*)l[LC_NUMERIC]->lconv.thousands_sep;
	//LC_TIME
	case D_T_FMT:
		return (char*)l[LC_TIME]->time.d_t_fmt;
	case D_FMT:
		return (char*)l[LC_TIME]->time.d_fmt;
	case T_FMT:
		return (char*)l[LC_TIME]->time.t_fmt;
	case T_FMT_AMPM:
		return (char*)l[LC_TIME]->time.t_fmt_ampm;
	case AM_STR:
		return (char*)l[LC_TIME]->time.am;
	case PM_STR:
		return (char*)l[LC_TIME]->time.pm;
	//LC_MESSAGES
	case YESEXPR:
		return (char*)l[LC_MESSAGES]->messages.yesexpr;
	case NOEXPR:
		return (char*)l[LC_MESSAGES]->messages.noexpr;
	default:
		return NULL;
	}
}
