#include <time.h>
#include <locale.h>

size_t strftime(char *buf, size_t size, const char *fmt, const struct tm *tm){
	return strftime_l(buf,size,fmt,tm,uselocale((locale_t)0));
}
