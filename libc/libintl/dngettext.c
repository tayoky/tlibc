#include <libintl.h>

char *dngettext(const char *domainname, const char *msgid1, const char *msgid2, unsigned long n) {
	return dcngettext(domainname, msgid1, msgid2, n, LC_MESSAGES);
}
