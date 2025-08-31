#include <locale.h>

//by default init to posix locale

const struct __locale __posix = {
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

struct __locale _locale = __posix;
