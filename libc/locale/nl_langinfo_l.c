#include <locale-internal.h>
#include <langinfo.h>

char *nl_langinfo_l(nl_item item, locale_t locale) {
	int category = _NL_ITEM_CATEGORY(item);
	int index    = _NL_ITEM_INDEX(item);
	if (locale == LC_GLOBAL_LOCALE) locale = __global_locale;
	const struct __locale_data *data = locale->data[category];
	
	if (index == _NL_ITEM_INDEX(-1)) {
		return (char*)data->name;
	}

	if (index >= (int)data->count) return NULL;
	return (char*)data->data[index].string;
}
