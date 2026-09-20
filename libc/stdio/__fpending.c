#include <stdio_ext.h>
#include <stdio-internal.h>

size_t __fpending(FILE *stream) {
    return stream ? stream->usedsize : 0;
}
