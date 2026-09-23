#include <stdio_ext.h>
#include <stdio-internal.h>

size_t __fpending(FILE *stream) {
    return stream->write_pos ? stream->write_pos - stream->buf : 0;
}
