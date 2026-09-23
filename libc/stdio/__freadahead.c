#include <stdio_ext.h>
#include <stdio-internal.h>

size_t __freadahead(FILE *stream) {
    return stream->read_end - stream->read_pos;
}
