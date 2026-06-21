#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

// TODO : use memstream
int vasprintf(char **restrict strp, const char *restrict fmt, va_list args) {
	va_list args2;
	va_copy(args2, args);
	char str[4096];
	int len = vsnprintf(str, sizeof(str), fmt, args2);
	va_end(args2);

	if (len < 0) return len;
	if (len < (int)sizeof(str)) {
		*strp = strdup(str);
		if (!*strp) return -1;
		return len;
	}

	char *buf = malloc(len + 1);
	if (!buf) return -1;
	*strp = buf;

	return vsnprintf(buf, len + 1, fmt, args);
}
