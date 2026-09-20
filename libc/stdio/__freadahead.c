#include <stdio_ext.h>

size_t __freadahead(FILE *stream) {
    // currently there is no read buffering
    (void)stream;
    return 0;
}
