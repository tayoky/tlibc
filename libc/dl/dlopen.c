#include <dlfcn.h>
#include <stddef.h>

#ifndef __DYNAMIC__
void *dlopen(const char *path, int flags){
    (void)path;
    (void)flags;
    return NULL;
}
#endif
