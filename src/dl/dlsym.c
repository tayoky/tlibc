#include <dlfcn.h>
#include <stddef.h>

void *dlsym(void *handle, const char *symbol){
    (void)handle;
    (void)symbol;
    return NULL;
}
