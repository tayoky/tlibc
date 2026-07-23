#include <libintl.h>

char *gettext(const char *msgid) {
	return dcgettext(NULL, msgid, LC_MESSAGES);
}
