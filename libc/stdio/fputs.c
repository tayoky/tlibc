#include <stdio.h>
#include <stdio-internal.h>
#include <string.h>

int fputs(const char *str, FILE *stream){
	return __fileio_write(stream, str, strlen(str)) < 0 ? -1 : 0;
}
