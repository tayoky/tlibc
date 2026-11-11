#ifndef LOCALE_INTERNAL_H
#define LOCALE_INTERNAL_H

#include <locale.h>
#include <langinfo.h>
#include <tlibc.h>
#include <stdint.h>

struct __locale_data {
	const char *name;
	void *file;
	size_t file_size;
	size_t count;
	union {
		const char *string;
		const uint32_t *wstring;
		int number;
	} data[];
};

struct __locale {
	const struct __locale_data *data[13];
};

extern const struct __locale __c_locale;
extern locale_t __global_locale;

#define _NL_CURRENT_LOCALE (__get_uthread()->locale ? (locale_t)__get_uthread()->locale : __global_locale)
#define _NL_CURRENT(category, index) (_NL_CURRENT_LOCALE->data[category]->data[_NL_ITEM_INDEX(index)])

#endif
