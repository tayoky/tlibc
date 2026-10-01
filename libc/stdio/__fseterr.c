#include <stdio-internal.h>
#include <stdio_ext.h>

void __fseterr(FILE *stream) {
	stream->error = 1;
}
