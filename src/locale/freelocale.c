#include <locale.h>
#include <stdlib.h>

void freelocale(locale_t locale){
	if (locale->allocated) free(locale);
}
