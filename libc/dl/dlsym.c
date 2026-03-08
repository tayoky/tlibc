#include <dlfcn.h>
#include <stddef.h>

#ifndef __DYNAMIC__
void *dlsym(void *handle, const char *symbol){
    (void)handle;
    (void)symbol;
    return NULL;
}
#endif
