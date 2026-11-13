#include <string.h>

void *memmem(const void *haystack, size_t hsize, const void *needle, size_t nsize) {
    const unsigned char *str1 = haystack;
    const unsigned char *str2 = needle;
    for (size_t i = 0; hsize - i >= nsize; i++) {
        for (size_t j = 0; j < nsize; j++) {
            if (str1[i + j] != str2[j]) {
                goto mismatch;
            }
        }
        return (void*)&str1[i];

mismatch:
        continue;
    }
    return NULL;
}
