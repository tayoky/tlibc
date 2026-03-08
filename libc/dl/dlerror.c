#include <dlfcn.h>

__attribute__((weak)) char *dlerror(void){
#ifdef __DYNAMIC__
    return "Dynamic linker is not loaded";
#else
    return "Executable is staticly linked";
#endif
}
