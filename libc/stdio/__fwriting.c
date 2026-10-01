#include <stdio-internal.h>
#include <stdio_ext.h>

int __fwriting(FILE *stream) {
	return stream->write_pos != NULL;
}
