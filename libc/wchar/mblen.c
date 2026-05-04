#include <wchar.h>

int mblen(const char *str, size_t n) {
    return mbtowc(NULL, str, n);
}