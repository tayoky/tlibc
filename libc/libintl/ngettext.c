#include <libintl.h>

char *ngettext(const char *msgid1, const char *msgid2, unsigned long n) {
	return dcngettext(NULL, msgid1, msgid2, n, LC_MESSAGES);
}
