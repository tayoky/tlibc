#include <locale.h>
#include <langinfo.h>

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
