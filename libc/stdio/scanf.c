#include <stdio.h>
#include <stdarg.h>

int scanf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int ret = vfscanf(stdin, fmt, args);
    va_end(args);
    return ret;
}
