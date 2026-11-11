#include <locale-internal.h>
#include <time.h>

size_t strftime(char *buf, size_t size, const char *fmt, const struct tm *tm) {
	return strftime_l(buf, size, fmt, tm, _NL_CURRENT_LOCALE);
}
