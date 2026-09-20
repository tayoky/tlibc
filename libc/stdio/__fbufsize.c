#include <stdio_ext.h>
#include <stdio-internal.h>

size_t __fbufsize(FILE *stream) {
    return stream ? stream->bufsize : 0;
}
