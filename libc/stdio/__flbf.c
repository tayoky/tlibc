#include <stdio-internal.h>
#include <stdio_ext.h>

int __flbf(FILE *stream) {
	return stream->buftype == _IOLBF;
}
