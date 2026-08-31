#include <string.h>

char *strtok(char *str, const char *delim) {
	static char *ptr;
	return strtok_r(str, delim, &ptr);
}
