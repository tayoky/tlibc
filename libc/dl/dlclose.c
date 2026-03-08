#include <dlfcn.h>

#ifndef __DYNAMIC__

int dlclose(void *handle){
    (void)handle;
    return -1;
}
#endif
