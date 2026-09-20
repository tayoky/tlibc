#include <stdio_ext.h>
#include <stdio-internal.h>

void  __fpurge(FILE *stream) {
    if (!stream) return;
    stream->unget = EOF;
    stream->usedsize = 0;
}
