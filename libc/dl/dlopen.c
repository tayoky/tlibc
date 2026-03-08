#include <dlfcn.h>
#include <stddef.h>

__attribute__((weak)) void *dlopen(const char *path, int flags){
    (void)path;
    (void)flags;
    return NULL;
}
