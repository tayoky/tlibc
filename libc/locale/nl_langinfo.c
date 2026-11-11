#include <langinfo.h>
#include <locale-internal.h>

char *nl_langinfo(nl_item item) {
	return nl_langinfo_l(item, _NL_CURRENT_LOCALE);
}
