#include <langinfo.h>
#include <locale-internal.h>

#define LC_CTYPE    0
#define LC_NUMERIC  1
#define LC_TIME     2
#define LC_COLLATE  3
#define LC_MONETARY 4
#define LC_MESSAGES 5
#define LC_ALL      6

#define LC_PAPER          7
#define LC_NAME           8
#define LC_ADDRESS        9
#define LC_TELEPHONE      10
#define LC_MEASUREMENT    11
#define LC_IDENTIFICATION 12

// by default init to the C locale

static const char not_available[] = "\177";

static const struct __locale_data __c_locale_ctype = {
	.name = "C",
	.count = _NL_ITEM_INDEX(_NL_NUM_LC_CTYPE),
	.data = {
		// TODO
		{ .string = "ANSI_X3.4-1968" },
	},
};

static const struct __locale_data __c_locale_numeric = {
	.name = "C",
	.count = _NL_ITEM_INDEX(_NL_NUM_LC_MESSAGES),
	.data = {
		{ .string = "." },
		{ .string = "" },
		{ .string = "" },
		{ .number = (unsigned int)L'.' },
		{ .number = (unsigned int)L'\0' },
		{ .string = "ANSI_X3.4-1968" },
	},
};

static const struct __locale_data __c_locale_time = {
	.name = "C",
	.count = _NL_ITEM_INDEX(_NL_NUM_LC_TIME),
	.data = {
		{ .string = "Sun" },
	    { .string = "Mon" },
	    { .string = "Tue" },
	    { .string = "Wed" },
		{ .string = "Thu" },
	    { .string = "Fri" },
	    { .string = "Sat" },
	    { .string = "Sunday" },
	    { .string = "Monday" },
	    { .string = "Tuesday" },
	    { .string = "Wednesday" },
	    { .string = "Thursday" },
	    { .string = "Friday" },
	    { .string = "Saturday" },
		{ .string = "Jan" },
		{ .string = "Feb" },
	    { .string = "Mar" },
	    { .string = "Apr" },
	    { .string = "May" },
	    { .string = "Jun" },
	    { .string = "Jul" },
	    { .string = "Aug" },
	    { .string = "Sep" },
	    { .string = "Oct" },
	    { .string = "Nov" },
		{ .string = "Dec" },
	    { .string = "January" },
	    { .string = "February" },
	    { .string = "March" },
	    { .string = "April" },
		{ .string = "May" },
	    { .string = "June" },
	    { .string = "July" },
	    { .string = "August" },
	    { .string = "September" },
	    { .string = "October" },
	    { .string = "November" },
		{ .string = "December" },
	    { .string = "AM" },
	    { .string = "PM" },
	    { .string = "%a %b %e %H:%M:%S %Y" },
		{ .string = "%m/%d/%y" },
	    { .string = "%H:%M:%S" },
	    { .string = "%I:%M:%S %p" },
	    { .string = "" },
		{ .string = "" },
	    { .string = "" },
		{ .string = "" },
	    { .string = "" },
	    { .string = "" },
	    { .number = 0 },
	    { .string = "" },
	    { .wstring = (const uint32_t *) L"Sun" },
	    { .wstring = (const uint32_t *) L"Mon" },
	    { .wstring = (const uint32_t *) L"Tue" },
	    { .wstring = (const uint32_t *) L"Wed" },
	    { .wstring = (const uint32_t *) L"Thu" },
	    { .wstring = (const uint32_t *) L"Fri" },
	    { .wstring = (const uint32_t *) L"Sat" },
	    { .wstring = (const uint32_t *) L"Sunday" },
	    { .wstring = (const uint32_t *) L"Monday" },
	    { .wstring = (const uint32_t *) L"Tuesday" },
	    { .wstring = (const uint32_t *) L"Wednesday" },
	    { .wstring = (const uint32_t *) L"Thursday" },
	    { .wstring = (const uint32_t *) L"Friday" },
	    { .wstring = (const uint32_t *) L"Saturday" },
	    { .wstring = (const uint32_t *) L"Jan" },
	    { .wstring = (const uint32_t *) L"Feb" },
	    { .wstring = (const uint32_t *) L"Mar" },
	    { .wstring = (const uint32_t *) L"Apr" },
		{ .wstring = (const uint32_t *) L"May" },
	    { .wstring = (const uint32_t *) L"Jun" },
	    { .wstring = (const uint32_t *) L"Jul" },
	    { .wstring = (const uint32_t *) L"Aug" },
	    { .wstring = (const uint32_t *) L"Sep" },
	    { .wstring = (const uint32_t *) L"Oct" },
	    { .wstring = (const uint32_t *) L"Nov" },
	    { .wstring = (const uint32_t *) L"Dec" },
	    { .wstring = (const uint32_t *) L"January" },
	    { .wstring = (const uint32_t *) L"February" },
	    { .wstring = (const uint32_t *) L"March" },
	    { .wstring = (const uint32_t *) L"April" },
	    { .wstring = (const uint32_t *) L"May" },
	    { .wstring = (const uint32_t *) L"June" },
	    { .wstring = (const uint32_t *) L"July" },
	    { .wstring = (const uint32_t *) L"August" },
	    { .wstring = (const uint32_t *) L"September" },
	    { .wstring = (const uint32_t *) L"October" },
	    { .wstring = (const uint32_t *) L"November" },
	    { .wstring = (const uint32_t *) L"December" },
	    { .wstring = (const uint32_t *) L"AM" },
	    { .wstring = (const uint32_t *) L"PM" },
	    { .wstring = (const uint32_t *) L"%a %b %e %H:%M:%S %Y" },
	    { .wstring = (const uint32_t *) L"%m/%d/%y" },
		{ .wstring = (const uint32_t *) L"%H:%M:%S" },
		{ .wstring = (const uint32_t *) L"%I:%M:%S %p" },
	    { .wstring = (const uint32_t *) L"" },
	    { .wstring = (const uint32_t *) L"" },
	    { .wstring = (const uint32_t *) L"" },
	    { .wstring = (const uint32_t *) L"" },
	    { .wstring = (const uint32_t *) L"" },
	    { .string = "\7" },
	    { .number = 19971130 },
	    { .string = "\4" },
	    { .string = "\1" },
	    { .string = "\2" },
	    { .string = "\1" },
	    { .string = "" },
	    { .string = "%a %b %e %H:%M:%S %Z %Y" },
	    { .wstring = (const uint32_t *) L"%a %b %e %H:%M:%S %Z %Y" },
	},
};

static const struct __locale_data __c_locale_collate = {
	.name = "C",
	.count = _NL_ITEM_INDEX(_NL_NUM_LC_MESSAGES),
	.data = {
		{ .number = 0 },
		{ .string = NULL },
		{ .string = NULL },
		{ .string = NULL },
		{ .string = NULL },
		{ .string = NULL },
		{ .string = NULL },
		{ .string = NULL },
		{ .string = NULL },
		{ .string = NULL },
		{ .string = NULL },
		{ .string = NULL },
		{ .string = NULL },
		{ .string = NULL },
		{ .string = NULL },
		{ .string = NULL },
		{ .string = NULL },
		{ .string = NULL },
		{ .string = "ANSI_X3.4-1968" },
	},
};

static const struct __locale_data __c_locale_monetary = {
	.name = "C",
	.count = _NL_ITEM_INDEX(_NL_NUM_LC_MONETARY),
	.data = {
		{ .string = "" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "" },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = "-" },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = "" },
		{ .string = "" },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = not_available },
		{ .string = not_available },
		{ .number = 10101 },
		{ .number = 99991231 },
		{ .number = 10101 },
		{ .number = 99991231 },
		{ .number = 1 },
		{ .number = (unsigned int)L'\0' },
		{ .number = (unsigned int)L'\0' },
		{ .string = "ANSI_X3.4-1968" },
	},
};

static const struct __locale_data __c_locale_messages = {
	.name = "C",
	.count = _NL_ITEM_INDEX(_NL_NUM_LC_MESSAGES),
	.data = {
		{ .string = "^[yY]" },
		{ .string = "^[nN]" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "ANSI_X3.4-1968" },
	},
};

static const struct __locale_data __c_locale_paper = {
	.name = "C",
	.count = _NL_ITEM_INDEX(_NL_NUM_LC_PAPER),
	.data = {
		{ .number = 297 },
		{ .number = 210 },
		{ .string = "ANSI_X3.4-1968" },
	},
};

static const struct __locale_data __c_locale_name = {
	.name = "C",
	.count = _NL_ITEM_INDEX(_NL_NUM_LC_NAME),
	.data = {
		{ .string = "%p%t%g%t%m%t%f" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "ANSI_X3.4-1968" },
	},
};

static const struct __locale_data __c_locale_address = {
	.name = "C",
	.count = _NL_ITEM_INDEX(_NL_NUM_LC_ADDRESS),
	.data = {
		{ .string = "%a%N%f%N%d%N%b%N%s %h %e %r%N%C-%z %T%N%c%N" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "ANSI_X3.4-1968" },
	},
};

static const struct __locale_data __c_locale_telephone = {
	.name = "C",
	.count = _NL_ITEM_INDEX(_NL_NUM_LC_TELEPHONE),
	.data = {
		{ .string = "+%c %a %l" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "ANSI_X3.4-1968" },
	},
};

static const struct __locale_data __c_locale_measurement = {
	.name = "C",
	.count = _NL_ITEM_INDEX(_NL_NUM_LC_MEASUREMENT),
	.data = {
		{ .string = "\1" },
		{ .string = "ANSI_X3.4-1968" },
	},
};

static const struct __locale_data __c_locale_identification = {
	.name = "C",
	.count = _NL_ITEM_INDEX(_NL_NUM_LC_MEASUREMENT),
	.data = {
		{ .string = "ISO/IEC 14652 i18n FDCC-set" },
		{ .string = "ISO/IEC JTC1/SC22/WG20 - internationalization" },
		{ .string = "" },
		{ .string = "Tayoky" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "ISO" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "" },
		{ .string = "1.0" },
		{ .string = "2026-11-11" },
		{ .string = "i18n:1999\0" "i18n:1999\0" "i18n:1999\0" "i18n:1999\0"
	      "i18n:1999\0" "i18n:1999\0" "\0"          "i18n:1999\0"
	      "i18n:1999\0" "i18n:1999\0" "i18n:1999\0" "i18n:1999\0"
	      "i18n:1999\0" "i18n:1999\0" "i18n:1999\0" "i18n:1999\0"
	      "i18n:1999" },
		{ .string = "ANSI_X3.4-1968" },
	},
};

const struct __locale __c_locale = {
	.data = {
		&__c_locale_ctype,
		&__c_locale_numeric,
		&__c_locale_time,
		&__c_locale_collate,
		&__c_locale_monetary,
		&__c_locale_messages,
		NULL, // LC_ALL
		&__c_locale_paper,
		&__c_locale_name,
		&__c_locale_address,
		&__c_locale_telephone,
		&__c_locale_measurement,
		&__c_locale_identification,
	},
};

locale_t __global_locale = (locale_t)&__c_locale;
