#include <libintl.h>

char *dgettext(const char *domainname, const char *msgid) {
	return dcgettext(domainname, msgid, LC_MESSAGES);
}
