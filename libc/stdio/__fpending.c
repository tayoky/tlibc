#include <stdio_ext.h>

size_t __fpending(FILE *stream) {
    return stream ? stream->usedsize : 0;
}
