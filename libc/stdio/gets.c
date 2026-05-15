#include <limits.h>
#include <stdio.h>

char *gets(char *buffer) {
	return fgets(buffer, INT_MAX, stdin);
}
