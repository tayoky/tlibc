#include <dlfcn.h>
#include <stddef.h>

void *dlopen(const char *path, int flags){
    (void)path;
    (void)flags;
    return NULL;
}
