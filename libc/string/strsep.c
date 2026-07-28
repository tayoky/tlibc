#include <string.h>

char *strsep(char **restrict strp, const char *restrict delim) {
	if (!strp || !*strp) {
		return NULL;
	}

	char *tok = *strp;
	*strp = strpbrk(tok, delim);
	if (*strp) {
		**strp = '\0';
		(*strp)++;
	}
	return tok;
}
