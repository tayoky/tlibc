#include <dlfcn.h>
#include <stddef.h>

__attribute__((weak)) void *dlsym(void *handle, const char *symbol){
    (void)handle;
    (void)symbol;
    return NULL;
}
