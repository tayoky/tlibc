#include <locale.h>
#include <langinfo.h>

char *nl_langinfo_l(nl_item item, locale_t locale){
	const struct __locale_data **l = locale->locales;
	if(item >= DAY_1 && item <= DAY_7){
		return l[LC_TIME]->time.day[item-DAY_1];
	}
	if(item >= ABDAY_1 && item <= ABDAY_7){
		return l[LC_TIME]->time.day[item-ABDAY_1];
	}
	if(item >= MON_1 && item <= MON_12){
		return l[LC_TIME]->time.day[item-MON_1];
	}
	if(item >= ABMON_1 && item <= ABMON_12){
		return l[LC_TIME]->time.day[item-ABMON_1];
	}

	switch(item){
	//LC_NUMERIC
	case RADIXCHAR:
		return l[LC_NUMERIC]->lconv.decimal_point;
	case THOUSEP:
		return l[LC_NUMERIC]->lconv.thousands_sep;
	//LC_TIME
	case D_T_FMT:
		return l[LC_TIME]->time.d_t_fmt;
	case D_FMT:
		return l[LC_TIME]->time.d_fmt;
	case T_FMT:
		return l[LC_TIME]->time.t_fmt;
	case T_FMT_AMPM:
		return l[LC_TIME]->time.t_fmt_ampm;
	case AM_STR:
		return l[LC_TIME]->time.am;
	case PM_STR:
		return l[LC_TIME]->time.pm;
	//LC_MESSAGES
	case YESEXPR:
		return l[LC_MESSAGES]->messages.yesexpr;
	case NOEXPR:
		return l[LC_MESSAGES]->messages.noexpr;
	default:
		return NULL;
	}
}
