#include <stdio_ext.h>
#include <stdio-internal.h>

void  __fpurge(FILE *stream) {
    if (!stream) return;
    stream->unget = EOF;
	stream->write_pos = stream->write_end = NULL;
	stream->read_pos  = stream->read_end  = NULL;
}
