#include <locale-internal.h>
#include <limits.h>

struct lconv *localeconv(void) {
	static struct lconv ret;

	ret.decimal_point = (char*)_NL_CURRENT(LC_NUMERIC, DECIMAL_POINT).string;
	ret.thousands_sep = (char*)_NL_CURRENT(LC_NUMERIC, THOUSANDS_SEP).string;
	ret.grouping = (char*)_NL_CURRENT(LC_NUMERIC, GROUPING).string;
	if (ret.grouping[0] == CHAR_MAX || ret.grouping[0] == (char)-1) {
		ret.grouping = "";
	}
	ret.int_curr_symbol = (char*)_NL_CURRENT(LC_MONETARY, INT_CURR_SYMBOL).string;
	ret.currency_symbol = (char*)_NL_CURRENT(LC_MONETARY, CURRENCY_SYMBOL).string;
	ret.mon_decimal_point = (char*)_NL_CURRENT(LC_MONETARY, MON_DECIMAL_POINT).string;
	ret.mon_thousands_sep = (char*)_NL_CURRENT(LC_MONETARY, MON_THOUSANDS_SEP).string;
	ret.mon_grouping = (char*)_NL_CURRENT(LC_MONETARY, MON_GROUPING).string;
	if (ret.mon_grouping[0] == CHAR_MAX || ret.mon_grouping[0] == (char)-1) {
		ret.mon_grouping = "";
	}
	ret.positive_sign = (char*)_NL_CURRENT(LC_MONETARY, POSITIVE_SIGN).string;
	ret.negative_sign = (char*)_NL_CURRENT(LC_MONETARY, NEGATIVE_SIGN).string;
	ret.int_frac_digits = _NL_CURRENT(LC_MONETARY, INT_FRAC_DIGITS).string[0];
	ret.frac_digits = _NL_CURRENT(LC_MONETARY, FRAC_DIGITS).string[0];
	ret.p_cs_precedes = _NL_CURRENT(LC_MONETARY, P_CS_PRECEDES).string[0];
	ret.p_sep_by_space = _NL_CURRENT(LC_MONETARY, P_SEP_BY_SPACE).string[0];
	ret.n_cs_precedes = _NL_CURRENT(LC_MONETARY, N_CS_PRECEDES).string[0];
	ret.n_sep_by_space = _NL_CURRENT(LC_MONETARY, N_SEP_BY_SPACE).string[0];
	ret.p_sign_posn = _NL_CURRENT(LC_MONETARY, P_SIGN_POSN).string[0];
	ret.n_sign_posn = _NL_CURRENT(LC_MONETARY, N_SIGN_POSN).string[0];
	ret.int_p_cs_precedes = _NL_CURRENT(LC_MONETARY, INT_P_CS_PRECEDES).string[0];
	ret.int_p_sep_by_space = _NL_CURRENT(LC_MONETARY, INT_P_SEP_BY_SPACE).string[0];
	ret.int_n_cs_precedes = _NL_CURRENT(LC_MONETARY, INT_N_CS_PRECEDES).string[0];
	ret.int_n_sep_by_space = _NL_CURRENT(LC_MONETARY, INT_N_SEP_BY_SPACE).string[0];
	ret.int_p_sign_posn = _NL_CURRENT(LC_MONETARY, INT_P_SIGN_POSN).string[0];
	ret.int_n_sign_posn = _NL_CURRENT(LC_MONETARY, INT_N_SIGN_POSN).string[0];

	return &ret;
}
