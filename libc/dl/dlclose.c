#include <dlfcn.h>


__attribute__((weak)) int dlclose(void *handle){
    (void)handle;
    return -1;
}
