#include <locale.h>
#include <langinfo.h>

extern struct __locale _locale;

char *nl_langinfo(nl_item item){
	return nl_langinfo_l(item,&_locale);
}
