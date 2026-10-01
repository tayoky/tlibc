#include <stdio-internal.h>
#include <stdio_ext.h>

int __freading(FILE *stream) {
	return stream->read_pos != NULL;
}
