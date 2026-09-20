#include <stdio_ext.h>

size_t __fbufsize(FILE *stream) {
    return stream ? stream->bufsize : 0;
}
