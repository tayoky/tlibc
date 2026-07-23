#ifndef _LIBINTL_H
#define _LIBINTL_H

#include <locale.h>

char *gettext(const char *msgid) __attribute__((format_arg(1)));
char *dgettext(const char *domainname, const char *msgid) __attribute__((format_arg(2)));
char *dcgettext(const char *domainname, const char *msgid, int category) __attribute__((format_arg(2)));
char *ngettext(const char *msgid1, const char *msgid2, unsigned long n);
char *dngettext(const char *domainname, const char *msgid1, const char *msgid2, unsigned long n);
char *dcngettext(const char *domainname, const char *msgid1, const char *msgid2, unsigned long n, int category);
char *textdomain(const char *domainname);
char *bindtextdomain(const char *domainname, const char *dirname);
char *bind_textdomain_codeset(const char *domainname, const char *codeset);
#endif
